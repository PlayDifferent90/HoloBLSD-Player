#ifndef EVENTITEM_H
#define EVENTITEM_H

#include <QGraphicsItem>
#include <QBrush>
#include <QPen>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
class EventItem : public QGraphicsItem
{
public:
    EventItem(QGraphicsScene *_scene):QGraphicsItem(){

    };
    EventItem();

    QColor lightblue{118,152,179};
    int eventSize = 10;
    int rectHeight = 30;
    qreal outlineSize = 1;
    QBrush eventBrush {lightblue};
    QPen penBlack {Qt::black,outlineSize};
    QVector<QPointF> points;
    QPainter* painter;
public:
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QRectF boundingRect() const;
    void ShowText();
signals:
    void mouseHover();
};

#endif // EVENTITEM_H
