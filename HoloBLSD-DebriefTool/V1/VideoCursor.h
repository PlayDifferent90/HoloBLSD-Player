#ifndef VIDEOCURSOR_H
#define VIDEOCURSOR_H

#include <QGraphicsItem>
#include <QBrush>
#include <QPen>
#include <QPainter>
#include <QLine>
#include <QPolygonF>
#include <QVector>
#include <QPointF>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QObject>

class VideoCursor:public QObject ,public QGraphicsItem
{
    Q_OBJECT
public:
    explicit VideoCursor(QObject *parent = nullptr,QGraphicsItem *parentGraphic = nullptr);
    VideoCursor(float height, QObject *_parent = nullptr, QGraphicsItem *parentGRaphics=nullptr);
    void setHeight(float height){line.setP2(QPoint(0,height));}

    int videoLengthVC=2000;
    QSizeF calculateSize() const;
    QVector<QPointF> points;
    QBrush brush;
    QPen pen;
    QLine line;
    QPolygonF poly;//indicator head polygon
    bool pressed=false;
    float tlScale =1;
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    ~VideoCursor();

signals:
    void CursorMoved (float x);
};

#endif // VIDEOCURSOR_H
