#ifndef TIMELINECURSOR_H
#define TIMELINECURSOR_H

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
#include "theme.h"

class timelineCursor : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit timelineCursor(QObject *parent = nullptr,QGraphicsItem *parentGraphic = nullptr);
    timelineCursor(float height, QObject *_parent = nullptr, QGraphicsItem *parentGRaphics=nullptr);
    void setHeight(float height){line.setP2(QPoint(0,height));}
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    ~timelineCursor();

    int cursorSize = 8;
    int videoLengthVC=2000;
    bool pressed=false;
    float tlScale =1;
    QVector<QPointF> points;
    QPolygonF poly;//indicator head polygon
    QSizeF calculateSize() const;
    QBrush brush;
    QPen pen;
    QLine line;
    Theme* theme;

protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void CursorMoved (float x);

};

#endif // TIMELINECURSOR_H
