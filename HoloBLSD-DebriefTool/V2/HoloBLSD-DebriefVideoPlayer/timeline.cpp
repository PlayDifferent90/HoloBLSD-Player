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
    SetupTimeline(_length);
    fileOpener=_fileOpener;

    videoCursor = new timelineCursor(scene->sceneRect().height()*2);// non chiaro perchè *2
    DrawTimeLineAxis();
    scene->addItem(videoCursor);
    videoCursor->setZValue(101);
    view->setMouseTracking(true);
    this->setMouseTracking(true);

}

Timeline::~Timeline()
{
}

void Timeline::DrawActivity(Activity* _activity){

    //qDebug()<<QTime::currentTime().toString() <<"drawing activities ...";
    if(_activity->GetActID()%2!=0){
       DrawBackgroundNode(currentBGRow, timelineLength, _activity->GetNodes().count());
    }
    if(!_activity->GetNodes().empty()){
        foreach (Node* n, _activity->GetNodes()) {
                DrawNode(n, _activity->GetActID());
        }
    }
    currentBGRow+=_activity->GetNodes().count();

}

void Timeline::DrawBackgroundNode(int _posY, int _timeLineLength, int _numUsers){
    QRect* rect= new QRect(0,0,_timeLineLength,_numUsers*timelineNodeHeight);
    QGraphicsItem *itemBG = scene->addRect(*rect,theme->penLineTimeStop, theme->lineBGBrush);
    itemBG->setPos(0,(_posY)*timelineNodeHeight);
    itemBG->setZValue(10);

    //draw rect in colonna sx too
    delete rect; //todo: valutare if good
}

void Timeline::DrawNode(Node* _node, int _actID)
{
    int nodeLength = _node->GetFinish()->GetTime() - _node->GetStart()->GetTime();

    QRectF* rect = new QRectF(0,0,nodeLength*tlScale,timelineNodeHeight);
    QGraphicsItem *item = scene->addRect(*rect,theme->penBlack,theme->nodeBrush); //#themetag
    item->setPos(_node->GetStart()->GetTime()*tlScale,timelineNodeHeight * (_node->GetUserID()));  //user id + actid

    qDebug()<<"drawing :" << _node<< " at "<< _node->GetStart()->GetTime() << " node Lenght = " << nodeLength << " , node height"<< QString::number(timelineNodeHeight * (_node->GetUserID())) << " , timeline length " << timelineLength;
    item->setZValue(90);
    if(!_node->GetEvents().empty()){
        foreach (Timestamp* t, _node->GetEvents()) {
            QRectF* rect = new QRectF(0,0,10,timelineNodeHeight);
            QGraphicsItem *itemE = scene->addRect(*rect,theme->penBlack,theme->eventBrush); //#themetag
            itemE->setPos(t->GetTime()*tlScale,timelineNodeHeight * (_node->GetUserID()));
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

    qDebug()<<QTime::currentTime().toString() <<"flushing elements ...";
    foreach (QGraphicsItem *itm, scene->items()) {
        if(itm!=videoCursor){
            scene->removeItem(itm);
        }
    }
}

void Timeline::UpdateVideoCursorX(float x){
    videoCursor->setHeight(height()*2);
    videoCursor->setX((float)x);
}

void Timeline::SetNumbers(){

    qDebug()<<QTime::currentTime().toString() <<"Setting Numbers ...";
    int minNumberDistance = 100;
    int millisecOffset = 1000;
    float previousPosition =-minNumberDistance -1;

    for(int i =0; i < (timelineLength); i+=10*tlScale){
        qDebug()<< "video% = " <<(float)i/(float)timelineLength;
        QGraphicsTextItem  *item = scene->addText(QDateTime::fromSecsSinceEpoch(videoLength*((float)i/(float)timelineLength)).toString("mm:ss"));
        item->setDefaultTextColor(Qt::white);
        float actualPosition = i*tlScale;

        if(actualPosition - previousPosition > minNumberDistance){
            item->setPos(actualPosition,verNumberOffset);
            scene->addRect(QRect(actualPosition,verTimelineOffset,1,scene->height()),theme->penLineTimeStop,theme->yellow)->setZValue(0);

            previousPosition = actualPosition;
        } else{
            item->setOpacity(0);
        }
    }
}

void Timeline::SetScale(float _scale){
    tlScale=_scale/10;
    if(tlScale <1) tlScale = 1;
    qDebug()<<"Scale value : "<< tlScale;
    SetupTimeline(timelineLength);
    UpdateTimeline();
}
timelineCursor* Timeline::GetCursor(){
    return videoCursor;
}

void Timeline::UpdateTimeline(){

    QApplication::setOverrideCursor(Qt::WaitCursor);
    qDebug()<< QTime::currentTime().toString() << "entering Update";
    FlushTimeLineElement();
    DrawTimeLineAxis();

    if(!fileOpener->GetAtivities().empty()){
        foreach (Activity* act, fileOpener->GetAtivities()) {
           DrawActivity(act);
        }
    }
    qDebug()<<QTime::currentTime().toString() << "Emitting TimelineDrawn";
    emit TimelineDrawn();
    QApplication::restoreOverrideCursor();
}

void Timeline::SetFileOpener(FileOpener* _fileopener){
    fileOpener=_fileopener;
}
void Timeline::SetupTimeline(int _length){
    timelineLength=_length*tlScale;
    //UpdateTimeline();
}
void Timeline::SetVideoLength(int _videolength){
    videoLength = _videolength;
}
