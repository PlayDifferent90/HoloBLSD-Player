
#include "timeline.h"
#include "qapplication.h"


Timeline::Timeline(QWidget *parent) :
    QWidget(parent)
{
}
Timeline::Timeline(QGraphicsView *_view, QWidget *_parent,FileOpener* _fileOpener, int _length)
{
    theme = new Theme();
    /*create scene*/
    view = _view;
    scene = view->scene();
    timelineLengthStart = _length;
    SetupTimeline(timelineLengthStart);
    fileOpener=_fileOpener;

    videoCursor = new timelineCursor(scene->sceneRect().height()*2);// non chiaro perchè *2

    connect(videoCursor,&timelineCursor::CursorMoved, this, &Timeline::RetrieveVideoCursorX);
    DrawTimeLineAxis();
    scene->addItem(videoCursor);
    videoCursor->setZValue(101);
    view->setMouseTracking(true);
    this->setMouseTracking(true);

}

Timeline::~Timeline()
{
}

void Timeline::DrawActivity(Activity* _activity,int _actRow){
    qDebug()<< "drawing activity " << _activity->GetName();
    if(!_activity->GetNodes().empty()){
        foreach (Node* n, _activity->GetNodes()) {
                DrawNode(n, _actRow); //in caso di problemi di linea: prima era _actRow  <-- _activity->GetActID()
        }
    }        qDebug()<< "    drawing bg for " << _activity->GetName() << "at line "<< drawnNodes << " height (number of nodes) "<< _activity->GetUsersNumber();

    if(_actRow%2!=0){  //in caso di problemi di linea: prima era _actRow  <-- _activity->GetActID()
       DrawBackgroundNode(drawnNodes, timelineLength, _activity->GetUsersNumber());
       //emit signal for left column;
    }

    drawnNodes+=_activity->GetUsersNumber();
}

void Timeline::DrawBackgroundNode(int _posY, int _timeLineLength, int _numUsers){
    QRect* rect= new QRect(0,0,_timeLineLength,_numUsers*timelineNodeHeight);
    QGraphicsItem *itemBG = scene->addRect(*rect,theme->penLineTimeStop, theme->lineBGBrush);
    itemBG->setPos(0,(_posY+1)*timelineNodeHeight);
    itemBG->setZValue(10);

    //draw rect in colonna sx too
    delete rect; //todo: valutare if good
}

void Timeline::DrawNode(Node* _node, int _actID)
{
    int nodeLength = (_node->GetFinish()->GetTime() - _node->GetStart()->GetTime());

    QRectF* rect = new QRectF(0,0,(float)nodeLength/(float)videoLength *(float)timelineLength,timelineNodeHeight);
    QGraphicsItem *item = scene->addRect(*rect,theme->penBlack,theme->nodeBrush); //#themetag
    item->setPos((float)_node->GetStart()->GetTime()/(float)videoLength *(float)timelineLength,timelineNodeHeight * (1+ drawnNodes));  //user id + actid

    qDebug()<<"drawing :" << _node<< " at "<< (float)item->pos().x()<< " node Lenght = " << (float)nodeLength/(float)videoLength *(float)timelineLength << " , timeline length " << timelineLength;
    item->setZValue(90);
    if(!_node->GetEvents().empty()){
        foreach (Timestamp* t, _node->GetEvents()) {
            QRectF* rect = new QRectF(0,0,10,timelineNodeHeight);
            QGraphicsItem *itemE = scene->addRect(*rect,theme->penBlack,theme->eventBrush); //#themetag
            itemE->setPos((float)t->GetTime()/(float)videoLength *(float)timelineLength,timelineNodeHeight *(1+ drawnNodes));
            itemE->setZValue(95);
        }
    }

}

void Timeline::DrawTimeLineAxis()
{
    QGraphicsItem *item = scene->addRect(QRect(0,0,timelineLength,2),theme->penBlack,Qt::white);
    item->setZValue(100);
    item->setPos(QPointF(0,verTimelineOffset));
    SetNumbers();
}

void Timeline::FlushTimeLineElement(){

    drawnNodes=0;
    currentBGRow=0;
    //qDebug()<<QTime::currentTime().toString() <<"flushing elements ...";
    foreach (QGraphicsItem *itm, scene->items()) {
        if(itm!=videoCursor){
            scene->removeItem(itm);
        }
    }
    emit FlushedActivities();
}

void Timeline::UpdateVideoCursorX(float x){ // todo: this must become %
   // qDebug()<< "video cursor X input pos : " << x;
    videoCursor->setHeight(height()*2);
    videoCursor->setX((float)x*(float)timelineLength/(float)videoLength);
}

void Timeline::RetrieveVideoCursorX(float x){ // todo: this must become %
    //qDebug()<< "video cursor X moved to  : " << x;
    emit VideoCursorMoved(x);
}

void Timeline::SetNumbers(){
int nums=0;
    for (int t=0; t<timelineLength; t+=(float)timeMarkerDistance*tlScale/((int)tlScale) ){
        float posXPercentage = (float)t/(float)timelineLength;
        //qDebug()<<"drawing verical line at % : "<< posXPercentage << " with video length : " << videoLength<<"  ; video millisec = " << videoLength*posXPercentage<< " ; to string mm:ss : " << QDateTime::fromMSecsSinceEpoch(videoLength*posXPercentage).toString("mm:ss");
        QGraphicsTextItem  *item = scene->addText(QDateTime::fromMSecsSinceEpoch(videoLength*posXPercentage).toString("mm:ss"));
        item->setDefaultTextColor(Qt::white);
        item->setPos(t,verNumberOffset);
        scene->addRect(QRect(t,verTimelineOffset,1,scene->height()),theme->penLineTimeStop,theme->yellow)->setZValue(1);
        nums++;
    }
//qDebug()<< "printed " << nums << "numbers";

}

void Timeline::SetScale(float _scale){
    tlScale= 1 + (maxZoomScale-1)*(_scale/100);
    //qDebug()<<"Scale value : "<< tlScale;

    SetupTimeline(timelineLengthStart);
    videoCursor->setMovementScale((float)videoLength/(float)timelineLength);

    UpdateTimeline();
}
timelineCursor* Timeline::GetCursor(){
    return videoCursor;
}

void Timeline::UpdateTimeline(){

    QApplication::setOverrideCursor(Qt::WaitCursor);
    //qDebug()<< QTime::currentTime().toString() << "entering Update";
    FlushTimeLineElement();
    DrawTimeLineAxis();

    int actRow=0;
    if(!fileOpener->GetAtivities().empty()){
        foreach (Activity* act, fileOpener->GetAtivities()) {
           if(act->GetVisibility()){
            DrawActivity(act,actRow);
            actRow++;
           }
           emit AddedActivity(act->GetName());
        }
    }
    //qDebug()<<QTime::currentTime().toString() << "Emitting TimelineDrawn";
    emit TimelineDrawn();
    QApplication::restoreOverrideCursor();
}

void Timeline::SetFileOpener(FileOpener* _fileopener){
    fileOpener=_fileopener;
}
void Timeline::SetupTimeline(int _length){
    timelineLength=_length*tlScale;
    //qDebug()<< "timelinelength = "<< timelineLength;
    //UpdateTimeline();
}
void Timeline::SetVideoLength(int _videolength){
    videoLength = _videolength;

    maxZoomScale = (((float)videoLength/(float)maxMillisResolution)*(float)timeMarkerDistance)/(float)timelineLengthStart;
    //qDebug()<<"("<< videoLength<<"/"<<maxMillisResolution << "*"<< timeMarkerDistance << ")/" << timelineLengthStart;
   // qDebug()<< "max zoom scale = "<< maxZoomScale;

}
