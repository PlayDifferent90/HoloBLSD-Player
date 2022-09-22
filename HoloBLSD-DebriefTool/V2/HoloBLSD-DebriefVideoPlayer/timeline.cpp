#include "timeline.h"


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
    timelineLength = _length;
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
    if(_activity->GetActID()%2!=0){
        qDebug()<<"drawing BG";
       DrawBackgroundNode(currentBGRow, timelineLength, _activity->GetNodes().count());
    }
    if(!_activity->GetNodes().empty()){
        qDebug()<<"drawing Node";
        foreach (Node* n, _activity->GetNodes()) {
                DrawNode(n, _activity->GetActID());
        }
    }
    currentBGRow+=_activity->GetNodes().count();

}

void Timeline::DrawBackgroundNode(int _posY, int _timeLineLength, int _numUsers){
    QRect* rect= new QRect(0,0,_timeLineLength,_numUsers*timelineNodeHeight);
    QGraphicsItem *itemBG = scene->addRect(*rect,theme->penLineTimeStop, theme->greyBlue);
    itemBG->setPos(0,(_posY)*timelineNodeHeight);
    itemBG->setZValue(50);

    //draw rect in colonna sx too
    delete rect; //todo: valutare if good
}

void Timeline::DrawNode(Node* _node, int _actID)
{

    int nodeLength = _node->GetFinish()->GetTime() - _node->GetStart()->GetTime();

    qDebug()<<"node Lenght = " << nodeLength;
    QRectF* rect = new QRectF(0,0,nodeLength,timelineNodeHeight);
    QGraphicsItem *item = scene->addRect(*rect,theme->penBlack,theme->nodeBrush); //#themetag
    item->setPos(_node->GetStart()->GetTime(),timelineNodeHeight * (_node->GetUserID()+_actID-1));
    item->setZValue(90);
    if(!_node->GetEvents().empty()){
        foreach (Timestamp* t, _node->GetEvents()) {
            QRectF* rect = new QRectF(0,0,10,timelineNodeHeight);
            QGraphicsItem *itemE = scene->addRect(*rect,theme->penBlack,theme->eventBrush); //#themetag
            itemE->setPos(t->GetTime(),timelineNodeHeight * (_node->GetUserID()));
            itemE->setZValue(95);
        }
    }

}

void Timeline::DrawTimeLineAxis()
{
    QGraphicsItem *item = scene->addRect(QRect(0,0,timelineLength/tlScale,2),theme->penBlack,Qt::white);
    item->setZValue(100);
    item->setPos(QPointF(0,verTimelineOffset));
    SetNumbers();
}

void Timeline::FlushTimeLineElement(){
    foreach (QGraphicsItem *itm, scene->items()) {
        if(itm!=videoCursor){
            scene->removeItem(itm);
        }
    }
}

void Timeline::UpdateVideoCursorX(float x){
    videoCursor->setHeight(height()*2);
    videoCursor->setX(x);
}

void Timeline::SetNumbers(){

    int minNumberDistance = 100;
    int millisecOffset = 1000;
    float previousPosition =-minNumberDistance -1;

    for(int i =0; i < timelineLength/(1000*tlScale); i++){

        QGraphicsTextItem  *item = scene->addText(QDateTime::fromSecsSinceEpoch(i).toString("mm:ss"));
        item->setDefaultTextColor(Qt::white);
        float actualPosition = i*millisecOffset*tlScale;

        if(actualPosition - previousPosition > minNumberDistance){
            item->setPos(actualPosition,verNumberOffset);
            scene->addRect(QRect(actualPosition,verTimelineOffset,1,scene->height()),theme->penLineTimeStop,theme->nodeBrush)->setZValue(0);

            previousPosition = actualPosition;
        } else{
            item->setOpacity(0);
        }
    }
}

void Timeline::SetScale(float _scale){
    tlScale=_scale/100;
    qDebug()<<"Scale value : "<< tlScale;
    UpdateTimeline();
}
timelineCursor* Timeline::GetCursor(){
    return videoCursor;
}

void Timeline::UpdateTimeline(){
    FlushTimeLineElement();
    DrawTimeLineAxis();

    foreach (Activity* act, fileOpener->GetAtivities()) {
        DrawActivity(act);
    }

}

void Timeline::SetFileOpener(FileOpener* _fileopener){
    fileOpener=_fileopener;
}
