#include "eventItem.h"

QRectF EventItem::boundingRect()const {
    return QRectF(-eventSize,-eventSize,eventSize,eventSize);
}
void EventItem::paint(QPainter *_painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter = _painter;
    points<<QPointF(-eventSize,0)
            <<QPointF(0,eventSize)
              <<QPointF(eventSize,0)
                <<QPointF(0,-eventSize);
    painter->setPen(penBlack);
    painter->setBrush(eventBrush);
    painter->drawPolygon(points);
    setAcceptHoverEvents(true);
}

void EventItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    qDebug()<<"enter hovering";


}
void EventItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    qDebug()<<"leaving hovering";

}
