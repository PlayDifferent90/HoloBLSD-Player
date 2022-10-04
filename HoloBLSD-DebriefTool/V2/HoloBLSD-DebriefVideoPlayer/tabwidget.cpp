#include "tabwidget.h"
#include "mainwindow.h"

TabWidget::TabWidget( MainWindow* mainWin, QString _name, FileOpener* _fileOpener)
{
    theme = new Theme();
    SetWidgetDimention(mainWin);

    tabName = _name;
    layout = new QGridLayout(this);

    //left column
    summary = new Summary(this,leftColumnWidth,upperRowHeight/4, "this is the summary");
    activity = new ActivityList(this, leftColumnWidth,upperRowHeight/4,_fileOpener);

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
    timelineWid = new TimelineWidget(this, _fileOpener, (leftColumnWidth+centralColumnWidth + rightColumnMinWidth), upperRowHeight);

    //all together
    layout->addLayout(leftColumn,0,0,1,1);
    layout->addLayout(centralColumn,0,1,1,1);
    layout->addLayout(rightColumn,0,2,1,2);
    layout->addWidget(timelineWid,1,0,2,4);


   //connect only in tab masterafter the first user is added, create the master user and connect it to the signal
   //     connect(mainWin, &MainWindow::userAdded, this, &TabWidget::AddUserToInspector);
    //Actions
    connect(mainWin, &MainWindow::videoAdded, this, &TabWidget::OpenVideo);
    connect(mainWin, &MainWindow::addActivity, this, &TabWidget::AddActivity);
    //video
    connect(timelineWid->GetToolBar(), &TimelineToolBar::Play, videoPlayer->GetPlayer(),&QMediaPlayer::play);
    connect(timelineWid->GetToolBar(), &TimelineToolBar::Pause, videoPlayer->GetPlayer(),&QMediaPlayer::pause);
    connect(timelineWid->GetToolBar(), &TimelineToolBar::Stop, videoPlayer->GetPlayer(),&QMediaPlayer::stop);
    //audio
    connect(timelineWid->GetToolBar(), &TimelineToolBar::Volume, videoPlayer->GetPlayer(),&QMediaPlayer::setVolume);
    //timeline
    connect(timelineWid->GetToolBar(), &TimelineToolBar::Zoom, timelineWid->GetTimeline(),&Timeline::SetScale);
    //durata video -> lunghezza timeline
    connect(videoPlayer->GetPlayer(),&QMediaPlayer::durationChanged,timelineWid->GetTimeline(),&Timeline::SetVideoLength);
    // riproduzione video -> scorrimento timeline
    connect(videoPlayer->GetPlayer(),&QMediaPlayer::positionChanged,timelineWid->GetTimeline(),&Timeline::UpdateVideoCursorX);
    //scorrimento barra -> scorriemnto timeline
    connect(videoPlayer->GetSlider(), &QSlider::sliderMoved,timelineWid->GetTimeline(),&Timeline::UpdateVideoCursorX);
    //scorrimento timeline -> scorrimento barra
    connect(timelineWid->GetTimeline(),&Timeline::VideoCursorMoved, videoPlayer->GetSlider(), &QSlider::setValue); //todo, catch this signal in timeline e send back correct value
    //scorrimento timeline -> riproduzione video
    connect(timelineWid->GetTimeline()->GetCursor(),&timelineCursor::CursorMoved, videoPlayer->GetPlayer(), &QMediaPlayer::setPosition);


    //init
    timelineWid->GetToolBar()->PauseTriggered();
    connect(mainWin->GetFileOpener(), &FileOpener::FileRead, timelineWid->GetTimeline(), &Timeline::UpdateTimeline);
    connect(mainWin->GetFileOpener(), &FileOpener::FileRead, timelineWid->GetTimeline(), &Timeline::UpdateTimeline);
    connect(videoPlayer->GetPlayer(),&QMediaPlayer::durationChanged,timelineWid->GetToolBar(), &TimelineToolBar::ZoomOutTriggered);
    connect(mainWin, &MainWindow::userAdded, this, &TabWidget::AddUserToInspector);

    //populate activity list
    connect(timelineWid->GetTimeline(), &Timeline::AddedActivity, activity, &ActivityList::AddActivityInList);
    connect(timelineWid->GetTimeline(), &Timeline::FlushedActivities, activity, &ActivityList::FlushActivities);
    connect(activity, &ActivityList::DoubleClicked, timelineWid->GetTimeline(), &Timeline::UpdateTimeline);
    connect(activity, &ActivityList::Clicked, inspector, &Inspector::UpdateInspector);

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
    activityIDGenerator++;
    qDebug()<<"ID ACtivity: " << activityIDGenerator;
    activity->AddActivityItem(_text);
    Activity* act = new Activity(_text,activityIDGenerator);
    Node* nod = new Node(new Timestamp(50*activityIDGenerator,"banana", "ughetto"), "userID" );
    nod->SetFinish(new Timestamp(100*activityIDGenerator,"a", "b"));
    act->AddNode(nod);
    activities.append(act);
    //timelineWid->GetTimeline()->DrawActivity(activities.at(activityIDGenerator-1));
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
