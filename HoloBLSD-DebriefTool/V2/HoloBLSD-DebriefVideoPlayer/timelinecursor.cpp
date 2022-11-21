#include "timelinecursor.h"

timelineCursor::timelineCursor(QObject *parent,QGraphicsItem * parentGraphics)
    : QObject{parent},
      QGraphicsItem (parentGraphics)
{

}

timelineCursor::timelineCursor(float _height,QObject* _parent,QGraphicsItem* _parentGaphics)
{
    theme= new Theme();
    pen = QPen(theme->videoCursorBrush,2);
    brush = theme->videoCursorBrush;
    points<<QPointF(-cursorSize,-cursorSize)
         <<QPointF(0,cursorSize)
        <<QPointF(cursorSize,-cursorSize)
       <<QPointF(-cursorSize,-cursorSize);
    setHeight(_height);
    setAcceptHoverEvents(true);
    this->setAcceptDrops(true);

    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(ItemSendsGeometryChanges);
    parent = _parent;
}

timelineCursor::~timelineCursor(){

}

QSizeF timelineCursor::calculateSize()const
{
    float minX = points[0].x();
    float minY = points[0].y();
    float maxX = points[0].x();
    float maxY = points[0].y();
    for(QPointF point : points){
        if (point.x() < minX){
            minX = point.x();
        }
        if (point.x() > maxX)
            maxX = point.x();

        if (point.y() < minY){
            minY = point.y();
        }
        if (point.y() > maxY){
            maxY = point.y();
        }
    }
    return QSizeF(maxX-minX,line.p2().y()*0.70f);
}

QRectF timelineCursor::boundingRect() const
{
    QSizeF size = this->calculateSize();
    return QRectF(-cursorSize,-cursorSize,size.width(),size.height());
}

void timelineCursor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(pen);
    painter->drawLine(line);
    painter->setBrush(brush);
    painter->drawPolygon(points);
}


void timelineCursor::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pos = event->scenePos();
    this->setPos(pos.x(),y());
    isCursorMoved=true;
    QGraphicsItem::mouseMoveEvent(event);
update();
}

QVariant timelineCursor::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {
        QPointF newPos = value.toPointF();
       //qDebug()<< "cursor moved to : " << (float)newPos.x()*tlScale;
        newPos.setY(y());
        if(newPos.x() < 0){
            newPos.setX(0);
        }
        if(isCursorMoved){
            emit CursorMoved ((float) newPos.x()*tlScale);
            isCursorMoved=false;
        }
        return newPos;
    }
    return QGraphicsItem::itemChange(change, value);
}

void timelineCursor::setMovementScale(float _vcScale){
    tlScale = _vcScale;
  //  qDebug()<<"set vursor scale to " << _vcScale;
}
