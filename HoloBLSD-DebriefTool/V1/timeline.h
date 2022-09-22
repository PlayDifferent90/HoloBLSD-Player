#ifndef TIMELINE_H
#define TIMELINE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTransform>
#include <QDebug>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QPen>
#include <QBrush>
#include <QGraphicsItem>
#include <QPoint>
#include "VideoCursor.h"
#include "Track.h"
#include <QPolygon>
#include <QGraphicsSceneMouseEvent>
class TimeLine : public QWidget
{
    Q_OBJECT

public:
    explicit TimeLine(QWidget *parent = nullptr);
    TimeLine(QGraphicsView *_view, QWidget *_parent = nullptr);
    ~TimeLine();
    QGraphicsItem* ItemAt(QPointF position){return scene->itemAt(position,QTransform());}
    void SetFrame(int _frame){if(_frame < maxFrame)frame=_frame;}

    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsItem *indicatorItem;
    QGraphicsItem *indicatorHead;
    VideoCursor *videoCursor;
    int rectHeight = 30;
    int numOffset = -4;
    float tlScale =1;
    int tlVerticalOffset = 15;
    int eventSize = 15;



    qreal outlineSize = 0;

    QColor bluedimmed{45,114,178};
    QColor blue{57,92,107};
    QColor skyblue{74,123,157};
    QColor lightblue{118,152,179};
    QColor greyBlue{78,128,152};
    QColor lightgreen{166,211,160};
    QColor red{219,84,97};
    QColor orange{255,127,00};
    QColor yellow{243,255,185};
    QPen penBlue {blue,outlineSize};
    QPen penBlack {Qt::black,outlineSize};
    QBrush nodeBrush {greyBlue};
    QBrush eventBrush {lightblue};

    QColor verLineColor{70,70,70};
    QPen penLineTimeStop{verLineColor,1};

    //QPolygon poly;


    int frame;
    int minFrame,maxFrame;
    void DrawTimeLineElement(QString name,QPointF pos, QRect rect, QPen pen, QBrush brush);
    void FlushTimeLineElement();
    void UpdateVideoCursorX(float x);
    void MovingCursor();
    void DrawTimeLineAxis(float length);
    void SetNumbers(float length, float scale);
    void SetScale(float scale);
    void DrawEvent(QPointF pos);
    void DrawNode(QString name, QPointF pos, QRect rect);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void Hovering();
signals:
    void GetCursorX(qint64 position);

};

#endif // TIMELINE_H
