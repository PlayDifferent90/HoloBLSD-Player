#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QWidget>
#include <QObject>
#include <QFileDialog>
#include <QScrollArea>
#include <QListWidget>
#include <QLabel>
#include "mainwindow.h"
#include "qgridlayout.h"
#include "qtabwidget.h"
#include "activitylist.h"
#include "summary.h"
#include "mainwindow.h"
#include "inspector.h"
#include "videoplayer.h"
#include "timeline.h"
#include "timelinewidget.h"
#include "activity.h"

class TabWidget : public QWidget
{
    Q_OBJECT
public:
    TabWidget(MainWindow *mainWin, QString _name, FileOpener *_fileOpener= nullptr, int _tabNumber =0);
    ~TabWidget();
    QString *GetName();
    void OpenVideo(QString _fileName, int _fileNumber);
    void AddUserToInspector(QString _userName, int _fileNum);
private:
    QString name;
    QGridLayout* tabLayout;
    QWidget* upperHalf;
    QWidget* lowerHalf;
    QGridLayout* layout;
    Summary* summary;
    ActivityList* activity;
    Inspector* inspector;
    VideoPlayer* videoPlayer;
    QString tabName;
    TimelineWidget* timelineWid;
    Theme* theme;
    QGraphicsScene* timelineScene;
    QGraphicsView* timelineView;
    QList<Activity*> activities;
    FileOpener* fo;

    int leftColumnWidth = 350;
    int centralColumnWidth = 750;
    int rightColumnMinWidth  = 1080;
    int upperRowHeight = 720;
    int activityIDGenerator = 0;
    void SetWidgetDimention(MainWindow *_mainWin);
    void UpdateSummary();
    int tabNum;
    void ZoomVideoCoord();
signals:
    void ZoomVideoCoordinator(float videoPos);
};

#endif // TABWIDGET_H
