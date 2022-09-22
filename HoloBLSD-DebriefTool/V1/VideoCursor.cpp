
#include "VideoCursor.h"

int cursorSize = 8;
QColor cursorColor = QColor(183,134,32);

/*Constructor*/
VideoCursor::VideoCursor(QObject *parent,QGraphicsItem * parentGraphics)
    :QObject(parent),
    QGraphicsItem (parentGraphics)
{

};

VideoCursor::VideoCursor(float height,QObject * parent,QGraphicsItem * parentGaphics)
{
    pen = QPen(cursorColor,2);
    brush = QBrush(Qt::RoundCap);
    brush.setColor(cursorColor);
    points<<QPointF(-cursorSize,-cursorSize)
         <<QPointF(0,cursorSize)
        <<QPointF(cursorSize,-cursorSize)
       <<QPointF(-cursorSize,-cursorSize);
    setHeight(height);
    setAcceptHoverEvents(true);
    this->setAcceptDrops(true);

    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(ItemSendsGeometryChanges);
}

/*works in tandem with Paint*/
QSizeF VideoCursor::calculateSize()const
{
    float minX = points[0].x();
    float minY = points[0].y();
    float maxX = points[0].x();
    float maxY = points[0].y();
    for(QPointF point : points){
        if (point.x() < minX){
            minX = point.x();
        }
        if (point.y() < minY){
            minY = point.y();
        }
        if (point.x() > maxX){
            maxX = point.x();
        }
        if (point.y() > maxY){
            maxY = point.y();
        }
    }
    return QSizeF(maxX-minX,line.p2().y()*0.70f);
}

QRectF VideoCursor::boundingRect() const
{
    QSizeF size = this->calculateSize();
    return QRectF(-cursorSize,-cursorSize,size.width(),size.height());
}

void VideoCursor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(pen);
    painter->drawLine(line);
    painter->setBrush(brush);
    painter->drawPolygon(points);
}


void VideoCursor::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pos = event->scenePos();
    //qDebug()<<"move";
    if(pressed){
        this->setPos(pos.x(),y());

    }
    QGraphicsItem::mouseMoveEvent(event);
update();
}

QVariant VideoCursor::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {
        QPointF newPos = value.toPointF();
        newPos.setY(y());
        if(newPos.x() < 0){
            newPos.setX(0);
        }
        emit CursorMoved ((float) newPos.x());
        return newPos;
    }
    return QGraphicsItem::itemChange(change, value);
}


VideoCursor::~VideoCursor(){

}
