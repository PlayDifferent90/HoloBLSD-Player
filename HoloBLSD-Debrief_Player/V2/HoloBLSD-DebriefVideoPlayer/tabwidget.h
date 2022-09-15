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

class TabWidget : public QWidget
{
    Q_OBJECT
public:
    TabWidget(MainWindow *mainWin, QString _name);
    ~TabWidget();
    void OpenVideo(QString fileName);
    void AddUserToInspector(QString _userName);
    void AddActivity(QString _text);
    QString *GetName();
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


    int leftColumnWidth = 350;
    int centralColumnWidth = 750;
    int rightColumnMinWidth  = 600;
    int upperRowHeight = 720;
};

#endif // TABWIDGET_H
