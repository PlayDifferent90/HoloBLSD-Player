#ifndef TIMELINEWIDGET_H
#define TIMELINEWIDGET_H

#include "mainwindow.h"
#include "qgraphicsscene.h"
#include "qgraphicsview.h"
#include <QObject>
#include <QWidget>
#include <QScrollBar>
#include "qboxlayout.h"
#include "qscrollarea.h"
#include "timeline.h"
#include "timelinetoolbar.h"
#include "fileopener.h"

class TimelineWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TimelineWidget(MainWindow *_mw, QWidget *parent= nullptr, FileOpener *_fileOpener=nullptr, int _Width=0, int Height=0);

    Timeline *GetTimeline();
    TimelineToolBar *GetToolBar();
private:
    QScrollArea* toolbarArea;
    QGraphicsScene* timelineScene;
    QGraphicsView* timelineView;
    QGraphicsScene*  activityScene;
    QGraphicsView* activityView;
    Timeline* timeline;
    TimelineToolBar* toolbar;
    MainWindow* mainWindow;

    void ChangeSceneRect();
    void SaveData();
signals:

};

#endif // TIMELINEWIDGET_H
