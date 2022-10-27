#include "timeline.h"
#include "qapplication.h"


Timeline::Timeline(QWidget *parent) :
    QWidget(parent)
{
}
Timeline::Timeline(QGraphicsView *_view, QWidget *_parent,FileOpener* _fileOpener, int _length, QGraphicsScene* _sibling)
{
    theme = new Theme();
    /*create scene*/
    view = _view;
    scene = view->scene();
    timelineLengthStart = _length;
    SetupTimeline(timelineLengthStart);
    fileOpener = _fileOpener;
    sibling = _sibling;

    videoCursor = new timelineCursor(scene->sceneRect().height()*2);// non chiaro perchè *2

    //connect(videoCursor,&timelineCursor::CursorMoved, this, &Timeline::RetrieveVideoCursorX);
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
  // qDebug()<< "drawing activity " << _activity->GetName();
    QList<QString>  users;
    int nn =0;
    if(!_activity->GetVisibleNodes().empty()){
        users.empty();
        foreach (Node* n, _activity->GetVisibleNodes()) {
             if(!users.contains(n->GetUserID())){
                 users.append(n->GetUserID());
             }
             DrawNode(n, _actRow, users.count(), n->GetUserID());
             nn++;
        }
    }
   // qDebug()<< "    drawing bg for " << _activity->GetName() << "at line "<< drawnNodes << " height (number of nodes) "<< _activity->GetUsersNumber(false);
    if(_actRow%2!=0){
       DrawBackgroundNode(drawnNodes, timelineLength, _activity->GetUsersNumber(false));
    }
    if(nn>0){
        DrawBackgroundNodeSibling(_activity->GetName(), drawnNodes, _activity->GetUsersNumber(false),_actRow);
    }
    drawnNodes+=_activity->GetUsersNumber(false);
}

void Timeline::DrawBackgroundNode(int _posY, int _timeLineLength, int _numUsers){
    QRect* rect= new QRect(0,0,_timeLineLength,_numUsers*timelineNodeHeight);
    QGraphicsItem *itemBG = scene->addRect(*rect,theme->penLineTimeStop, theme->TimelineBGRow);
    itemBG->setPos(0,(_posY+1)*timelineNodeHeight);
    itemBG->setZValue(5);
    delete rect;
}

void Timeline::DrawBackgroundNodeSibling(QString _name,int _posY, int _numUsers,int _actRow){
    if(_actRow%2!=0){
        QRect* rect= new QRect(0,0,500,_numUsers*timelineNodeHeight);
        QGraphicsItem *itemBG = sibling->addRect(*rect,theme->penLineTimeStop, theme->TimelineBGRow);
        itemBG->setPos(0,(_posY+1)*timelineNodeHeight);
        itemBG->setZValue(0);
    }
    QGraphicsTextItem  *itemText = sibling->addText(_name);
    itemText->setScale(1.5);
    itemText->setDefaultTextColor(Qt::white);
    itemText->setPos(40,(_posY+((float)(_numUsers+1)/(float)2))*timelineNodeHeight );
    itemText->setZValue(10);
}


void Timeline::DrawNode(Node* _node, int _actID, int _usersNumb, QString _userID)
{
       // qDebug()<< "UserId "<< _userID;
    int nodeLength = (_node->GetFinish()->GetTime() - _node->GetStart()->GetTime());
   // qDebug()<<"nodeLength"<< nodeLength<<  "videoLength"<< videoLength << "timelineLength"<< timelineLength;

    QRectF* rect = new QRectF(0,0,(float)nodeLength/(float)videoLength *(float)timelineLength,timelineNodeHeight);
    QGraphicsItem *item = scene->addRect(*rect,theme->timelineNodeBorders,theme->RandomUserColor(_userID)); //#themetag
    item->setPos((float)_node->GetStart()->GetTime()/(float)videoLength *(float)timelineLength,timelineNodeHeight * (_usersNumb+ drawnNodes));  //user id + actid

    //qDebug()<<"drawing :" << _node<< " at "<< (float)item->pos().x()<< " node Lenght = " << (float)nodeLength/(float)videoLength *(float)timelineLength << " , timeline length " << timelineLength;
    item->setZValue(90);
    if(!_node->GetEvents().empty()){
        foreach (Timestamp* t, _node->GetEvents()) {
            QRectF* rect = new QRectF(0,0,5,timelineNodeHeight);
            QGraphicsItem *itemE = scene->addRect(*rect,theme->timelineNodeBorders,theme->eventBrush); //#themetag
            itemE->setPos((float)t->GetTime()/(float)videoLength *(float)timelineLength,timelineNodeHeight *(_usersNumb+ drawnNodes));
            itemE->setZValue(95);
        }
    }

}

void Timeline::DrawTimeLineAxis()
{
    QGraphicsItem *item = scene->addRect(QRect(0,0,timelineLength,2),theme->timelineNodeBorders,Qt::white);
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
    foreach (QGraphicsItem *itmAct, sibling->items()) {
            sibling->removeItem(itmAct);
    }
    emit FlushedActivities();
}

void Timeline::UpdateVideoCursorX(float x){
   // qDebug()<< "video cursor X input pos : " << x;
    videoCursor->setHeight(height()*2);
    videoCursor->setX(x*(float)timelineLength/(float)videoLength);
}

void Timeline::SetNumbers(){
int nums=0;
    for (int t=0; t<timelineLength; t+=(float)timeMarkerDistance*(float)tlScale/(tlScale) ){
        float posXPercentage = (float)t/(float)timelineLength;
        //qDebug()<<"drawing verical line at % : "<< posXPercentage << " with video length : " << videoLength<<"  ; video millisec = " << videoLength*posXPercentage<< " ; to string mm:ss : " << QDateTime::fromMSecsSinceEpoch(videoLength*posXPercentage).toString("mm:ss");
        QGraphicsTextItem  *item = scene->addText(QDateTime::fromMSecsSinceEpoch(videoLength*posXPercentage).toString("mm:ss"));
        item->setDefaultTextColor(Qt::white);
        item->setPos(t,verNumberOffset);
        scene->addRect(QRect(t,verTimelineOffset,1,scene->height()),theme->penLineTimeStop,theme->yellow)->setZValue(10);
        nums++;
    }
//qDebug()<< "printed " << nums << "numbers";
}

void Timeline::SetScale(float _scale){
    tlScale= 1 + (maxZoomScale-1)*(_scale/100);
    //qDebug()<<"maxZoomScale value : "<< maxZoomScale <<"_scale value : "<< tlScale;
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
    if(!fileOpener->GetActivities().empty()){
        foreach (Activity* act, fileOpener->GetActivities()) {
           if(act->GetVisibility()){
               //qDebug()<<"activity "<<act->GetName() << "in tab" << fileOpener->GetUser();
               DrawActivity(act,actRow);
               actRow++;
           }
           //qDebug()<<act->GetVisibility();
           emit AddedActivity(act->GetName(),act->GetVisibility());
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
    //qDebug()<< "timelinelength = "<< timelineLength << "length " << _length <<" scale"<<tlScale;
    //UpdateTimeline();
}
void Timeline::SetVideoLength(int _videolength){
    videoLength = _videolength;
    maxMillisResolution= _videolength*0.01;
    maxZoomScale = (((float)videoLength/(float)maxMillisResolution)*(float)timeMarkerDistance)/(float)timelineLengthStart;
    //qDebug()<<"("<< videoLength<<"/"<<maxMillisResolution << "*"<< timeMarkerDistance << ")/" << timelineLengthStart;
   // qDebug()<< "max zoom scale = "<< maxZoomScale;
}

int Timeline::GetTimelineLength(){
    return timelineLength;
}
