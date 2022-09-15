#include "tabwidget.h"
#include "mainwindow.h"

TabWidget::TabWidget( MainWindow* mainWin, QString _name)
{
    tabName = _name;
    layout = new QGridLayout(this);

    //left column
    summary = new Summary(this,leftColumnWidth,upperRowHeight/4, "this is the summary");
    activity = new ActivityList(this, leftColumnWidth,upperRowHeight/4);

    QVBoxLayout* leftColumn = new QVBoxLayout(this);
    leftColumn->addWidget(summary->SummaryWidget());
    leftColumn->addWidget(activity->ActivityWidget());

    //inspector
    inspector = new Inspector(this,centralColumnWidth, upperRowHeight);

    QVBoxLayout* centralColumn = new QVBoxLayout(this);
    centralColumn -> addWidget(inspector->InspectorWidget());

    //video
    videoPlayer = new VideoPlayer(this, "video_user" + _name, rightColumnMinWidth, upperRowHeight );

    QVBoxLayout* rightColumn = new QVBoxLayout(this);
    rightColumn -> addWidget(videoPlayer);

    //timeline
    QScrollArea* timelineScroll = new QScrollArea(this);
    timelineScroll->setMinimumHeight(720);

    //all together
    layout->addLayout(leftColumn,0,0,1,1);
    layout->addLayout(centralColumn,0,1,2,1);
    layout->addLayout(rightColumn,0,2,2,2);
    layout->addWidget(timelineScroll,2,0,2,4);

   //connect only in tab master.
    //after the first user is added, create the master user and connect it to the signal
   //     connect(mainWin, &MainWindow::userAdded, this, &TabWidget::AddUserToInspector);
    connect(mainWin, &MainWindow::videoAdded, this, &TabWidget::OpenVideo);
}

TabWidget::~TabWidget(){
    delete this;
}

void TabWidget::OpenVideo(QString fileName){

    qDebug()<<"opening file "<< fileName;
     videoPlayer->ShowVideo(fileName);
}

void TabWidget::AddUserToInspector(QString _userName){
    inspector->AddUserTab(_userName);
}

void TabWidget::AddActivity(QString _text){
    activity->AddActivityItem(_text);
}

QString* TabWidget::GetName(){
    return &tabName;
}
