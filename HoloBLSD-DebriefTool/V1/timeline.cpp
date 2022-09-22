#include "timeline.h"
//#include "graphics_view_zoom.h"
#include "qdatetime.h"
#include "QVector"
#include <QPolygon>
#include <QHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include "eventItem.h"


TimeLine::TimeLine(QWidget *parent) :
    QWidget(parent)
{
}

TimeLine::TimeLine(QGraphicsView *_view, QWidget *parent)
{
    /*create scene*/
    if (_view) view = _view;
    else view = new QGraphicsView(this);
    scene = view->scene();
    setMouseTracking(true);

    /*create cursor*/
    videoCursor = new VideoCursor(height());
    scene->addItem(videoCursor);
    videoCursor->setZValue(101);
    view->setMouseTracking(true);
    this->setMouseTracking(true);

}

TimeLine::~TimeLine()
{
}

//ereditare da track
void TimeLine::DrawEvent( QPointF pos){

    EventItem *event = new EventItem(scene);
    scene->addItem(event);
    event->setPos(pos+QPointF(0,(rectHeight)/2));

}

void TimeLine::DrawNode(QString name, QPointF pos, QRect rect)//, QPen pen, QBrush brush)
{
    QGraphicsItem *item = scene->addRect(rect,penBlack, nodeBrush);
    item->setPos(pos);

    //QGraphicsItem *itemText = scene->addText(name);
    QGraphicsTextItem *itemText = scene->addText(name);  // todo: nome sopra  non dentro allineato con vista
    itemText->setDefaultTextColor(Qt::white);
    //itemText->setTextWidth(item->x());    //<-- manda il testo a capo ma non lo cancella, si sovrapponme alla linea succesiva
    itemText->setZValue(100);
    itemText->setPos(pos);


}

void TimeLine::DrawTimeLineAxis(float length)
{
    QGraphicsItem *item = scene->addRect(QRect(0,0,length/tlScale,2),penBlack,Qt::white);
    item->setZValue(100);
    item->setPos(QPointF(0,tlVerticalOffset));
    SetNumbers(length,tlScale);
}

void TimeLine::FlushTimeLineElement(){
    foreach (QGraphicsItem *itm, scene->items()) {
        if(itm!=videoCursor){
            scene->removeItem(itm);
        }
    }
}

void TimeLine::UpdateVideoCursorX(float x){
    //(long term): spostare in videocursor
    videoCursor->setHeight(height()*2);
    videoCursor->setX(x);
}


void TimeLine::SetNumbers(float length, float scale){

    int minNumberDistance = 100;
    int millisecOffset = 1000;
    float previousPosition =-minNumberDistance -1;

    for(int i =0; i < length/(1000*scale); i++){

        QGraphicsTextItem  *item = scene->addText(QDateTime::fromSecsSinceEpoch(i).toString("mm:ss"));
        item->setDefaultTextColor(Qt::white);
        float actualPosition = i*millisecOffset*scale;

        if(actualPosition - previousPosition > minNumberDistance){
            item->setPos(actualPosition,numOffset);
            scene->addRect(QRect(actualPosition,tlVerticalOffset,1,scene->height()),penLineTimeStop,nodeBrush)->setZValue(0);

            previousPosition = actualPosition;
        } else{
            item->setOpacity(0);
        }
    }
}
void TimeLine::SetScale(float scale){
    tlScale=scale;
}
