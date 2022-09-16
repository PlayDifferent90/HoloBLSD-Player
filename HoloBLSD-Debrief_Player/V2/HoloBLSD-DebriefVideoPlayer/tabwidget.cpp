#include "tabwidget.h"
#include "mainwindow.h"

TabWidget::TabWidget( MainWindow* mainWin, QString _name)
{
    theme = new Theme();
    SetWidgetDimention(mainWin);

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
    videoPlayer = new VideoPlayer(this, "video - " + _name, rightColumnMinWidth, upperRowHeight );

    QVBoxLayout* rightColumn = new QVBoxLayout(this);
    rightColumn -> addWidget(videoPlayer);

    //timeline
    timeline = new TimelineWidget(this, (leftColumnWidth+centralColumnWidth + rightColumnMinWidth), upperRowHeight  /*,QList<QGRaphicsItem> Nodes */);

    //all together
    layout->addLayout(leftColumn,0,0,1,1);
    layout->addLayout(centralColumn,0,1,1,1);
    layout->addLayout(rightColumn,0,2,1,2);
    layout->addWidget(timeline,1,0,2,4);

   //connect only in tab masterafter the first user is added, create the master user and connect it to the signal
   //     connect(mainWin, &MainWindow::userAdded, this, &TabWidget::AddUserToInspector);
    connect(mainWin, &MainWindow::videoAdded, this, &TabWidget::OpenVideo);
}

TabWidget::~TabWidget(){
    delete this;
}

void TabWidget::OpenVideo(QString fileName){

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

void TabWidget::SetWidgetDimention(MainWindow* _mainWin){
    //todo: on resize di window chiamare la funzione per aggiornare dimensione dei widget
    int  colWidth=  _mainWin->size().width()*0.98;
    int  rowHeight= _mainWin->size().height();

    leftColumnWidth = colWidth/6;
    centralColumnWidth = colWidth/6*2;
    rightColumnMinWidth  = colWidth/6*3;
    upperRowHeight = rowHeight/2 *0.8;
}
