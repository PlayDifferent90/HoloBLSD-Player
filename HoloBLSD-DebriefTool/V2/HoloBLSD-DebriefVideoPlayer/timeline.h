#ifndef TIMELINE_H
#define TIMELINE_H

#include <QObject>
#include <QWidget>
#include <QPolygon>
#include <QHoverEvent>
#include <QGraphicsSceneMouseEvent>
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
//#include "graphics_view_zoom.h"
#include "QVector"
#include "timelinecursor.h"
#include "activity.h"
#include "qboxlayout.h"
#include "qdatetime.h"
#include "fileopener.h"

class Timeline : public QWidget
{
    Q_OBJECT
public:
    ~Timeline();
    QGraphicsItem* ItemAt(QPointF position){return scene->itemAt(position,QTransform());}
    void SetFrame(int _frame){if(_frame < maxFrame)frame=_frame;}
    Timeline(QWidget *parent);
    Timeline();
    Timeline(QGraphicsView *_view, QWidget *_parent, FileOpener* _fileOpener, int _length);
    void DrawNode(QPointF pos, QRect rect);
    void DrawTimeLineAxis();
    void FlushTimeLineElement();
    void UpdateVideoCursorX(float x);
    void SetNumbers();
    void SetScale(float scale);
//private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    timelineCursor *videoCursor;
    Theme* theme;
    QGraphicsScene* timelineScene;
    QGraphicsView* timelineView;
    QGraphicsScene*  activitiesScene;
    QGraphicsView* activitiesView;
    FileOpener* fileOpener;

    int frame;
    int minFrame,maxFrame;
    float tlScale =1;

    int timelineLength = 1000;
    int timelineLengthStart = 1000;
    int videoLength = 1000;
    int timelineNodeHeight = 30;
    int verNumberOffset = -4;
    int verTimelineOffset = 15;
    int currentBGRow=1;
    int timeMarkerDistance = 150;
    int maxMillisResolution = 10*1000;
    float maxZoomScale = 1;

    void DrawBackgroundNode(int posY, int timeLineLength, int numUsers);
    void DrawActivity(Activity *_activity);
    void DrawNode(Node *_node, int _actID);
    timelineCursor *GetCursor();

    void UpdateTimeline();
    void SetFileOpener(FileOpener *_fileopener);
    void SetupTimeline(int _length);
    void SetVideoLength(int _videolength);
    void RetrieveVideoCursorX(float x);
signals:
    void TimelineDrawn();
    void VideoCursorMoved(int t);
};

#endif // TIMELINE_H
