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
#include <QGraphicsScene>
//#include "graphics_view_zoom.h"
#include "QVector"
#include "timelinecursor.h"
#include "activity.h"
#include "qboxlayout.h"
#include "qdatetime.h"
#include "fileopener.h"
#include "QLabel"

class Timeline : public QWidget
{
    Q_OBJECT
public:
    ~Timeline();
    QGraphicsItem* ItemAt(QPointF position){return scene->itemAt(position,QTransform());}
    void SetFrame(int _frame){if(_frame < maxFrame)frame=_frame;}
    Timeline(QWidget *parent);
    Timeline();
    Timeline(QGraphicsView *_view, QWidget *_parent, FileOpener* _fileOpener, int _length, QGraphicsScene *_sibling);
    void DrawNode(QPointF pos, QRect rect);
    void DrawTimeLineAxis();
    void FlushTimeLineElement();
    void UpdateVideoCursorX(float x);
    void SetNumbers();
    void SetScale(float scale);
    timelineCursor *GetCursor();
    void UpdateTimeline();
    void SetVideoLength(int _videolength);
    int GetTimelineLength();
private:
    QGraphicsScene *scene;
    QGraphicsScene *sibling;
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
    int drawnNodes =0;

    void DrawBackgroundNode(int posY, int timeLineLength, int numUsers);
    void DrawActivity(Activity *_activity);
    void SetFileOpener(FileOpener *_fileopener);
    void SetupTimeline(int _length);
    void DrawActivity(Activity *_activity, int _actRow);
    void DrawBackgroundNodeSibling(QString _name,int _posY, int _numUsers,int _actRow);
    void DrawNode(Node *_node, int _actID, int _usersNumb, QString _userID);
signals:
    void TimelineDrawn();
    void AddedActivity(QString name, bool visibility);
    void FlushedActivities();
};

#endif // TIMELINE_H
