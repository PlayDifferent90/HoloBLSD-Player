#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListIterator>


#include "timeline.h"
#include "activity.h"
#include "activityentry.h"
#include "events.h"
#include "QGraphicsSceneWheelEvent"
#include "QListWidget"
#include "QList"

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QFileDialog>
#include <QProgressBar>
#include <QSlider>

#include <QTimeLine>
#include <QXmlStreamReader>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void AddElement(QObject *object);
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //(long term): valutare quale di queste varaibili va in un file  init
    QGraphicsScene *scene;
    QGraphicsView *viewTimeLine;
    TimeLine *timeline;
    QList<Activity>* activityNodes;
    QList<ActivityEntry*> nodes;
    QList<ActivityEntry*> nodesTrigger;
    QList<ActivityEntry*> events;
    float videoLength=2000;
    float tlScale = 0.01 ;
    int i =0;
    int actNum =0;
    int timeLineWidth = 2;
    float minScale = 0;
    int errorsNum =0;
    int warningsNum =0;
    int err, war =0;

    void UpdateTimeLineRender(QString text);
    void UpdateTimeLineLength(float length);
    void UpdateTimeLine(float scale);
    float scaledVideoLength(float lineLength, float scale);
    void MoveVideoCursor(int moving);
    void SlotVideoCursor(float x);
    void AddActivityToTL(int _time, QString _owner, QString _type, QString _msg, int war, int err);
    void InspectorPopulator(QString _msg);
    void UpdateViewInit();
    void RepToCSV(QString actDuplicate);
    void InspectorPopulator(QString _msg, int _war, int _err);
    void DrawActivities();
    void PrintSignalDebug();
private slots:

    void on_listWidgetActivities_itemClicked(QListWidgetItem *item);

   // void on_actionformattedActivity_triggered();

    void on_pushButtonZoomOut_clicked();

    void on_pushButtonZoomIn_clicked();

    void on_actionOpenVideo_triggered();


    void on_stop_clicked();

    void on_pause_clicked();

    void on_play_clicked();

    void on_actionOpenLogs_triggered();

    void on_horizontalSliderZoom_sliderMoved(int position);

    void on_listWidgetActivities_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    QMediaPlayer* player;
    QVideoWidget* videoWidget;
    QProgressBar* bar;
    QSlider* slider;

    QTimeLine* timeLine;
signals:
    float SignalVideoCursor(float x);
};

#endif // MAINWINDOW_H
