#include "tabwidget.h"
#include "mainwindow.h"
#include "qapplication.h"

TabWidget::TabWidget( MainWindow* mainWin, QString _name, FileOpener* _fileOpener, int _tabNumber)
{
    theme = new Theme();
    SetWidgetDimention(mainWin);

    tabName = _name;
    tabNum = _tabNumber;
    layout = new QGridLayout(this);  
    fo = _fileOpener;

    //summary
    summary = new Summary(this,leftColumnWidth,upperRowHeight/4, "Summary Text");
    //activity list
    activity = new ActivityList(this, leftColumnWidth,upperRowHeight/4,fo);
    //timeline
    timelineWid = new TimelineWidget(mainWin, this, fo, (leftColumnWidth + centralColumnWidth + rightColumnMinWidth)*1.01, upperRowHeight);


    QVBoxLayout* leftColumn = new QVBoxLayout(this);
    leftColumn->addWidget(summary->SummaryWidget());
    leftColumn->addWidget(activity->ActivityWidget());

    //inspector
    inspector = new Inspector(this,centralColumnWidth, upperRowHeight,_fileOpener);

    QVBoxLayout* centralColumn = new QVBoxLayout(this);
    centralColumn -> addWidget(inspector->InspectorWidget());

    //video
    videoPlayer = new VideoPlayer(this, fo, rightColumnMinWidth, upperRowHeight );

    QVBoxLayout* rightColumn = new QVBoxLayout(this);
    rightColumn -> addWidget(videoPlayer);


    //all together
    layout->addLayout(leftColumn,0,0,1,1);
    layout->addLayout(centralColumn,0,1,1,1);
    layout->addLayout(rightColumn,0,2,1,2);
    layout->addWidget(timelineWid,1,0,2,4);


    //Actions
    connect(mainWin, &MainWindow::videoAdded, this, &TabWidget::OpenVideo);
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
    connect(videoPlayer->GetPlayer(),&QMediaPlayer::positionChanged,timelineWid->GetTimeline(),&Timeline::UpdateVideoCursorX); //issue
    //scorrimento barra -> scorriemnto timeline
    connect(videoPlayer->GetSlider(), &QSlider::sliderMoved,timelineWid->GetTimeline(),&Timeline::UpdateVideoCursorX);
    //scorrimento timeline -> scorrimento barra
    connect(timelineWid->GetTimeline()->GetCursor(),&timelineCursor::CursorMoved, videoPlayer->GetSlider(), &QSlider::setValue);
    //scorrimento timeline -> riproduzione video
    connect(timelineWid->GetTimeline()->GetCursor(),&timelineCursor::CursorMoved, videoPlayer->GetPlayer(), &QMediaPlayer::setPosition);
    //Scaling timeline whikle playing video
    connect(timelineWid->GetToolBar(), &TimelineToolBar::Zoom, this, &TabWidget::ZoomVideoCoord);
    connect(this, &TabWidget::ZoomVideoCoordinator, timelineWid->GetTimeline(),&Timeline::UpdateVideoCursorX);

    //init
    timelineWid->GetToolBar()->PauseTriggered();

    connect(mainWin->GetFileOpener(), &FileOpener::FileRead, timelineWid->GetTimeline(), &Timeline::UpdateTimeline);
    connect(mainWin->GetFileOpener(), &FileOpener::FileRead, this, &TabWidget::UpdateSummary);
    connect(mainWin->GetFileOpener(), &FileOpener::FileRead, inspector, &Inspector::PopulateInspector);

    connect(mainWin->GetFileOpener(), &FileOpener::MasterFileRead, inspector, &Inspector::PopulateMasterInspector);
    connect(mainWin->GetFileOpener(), &FileOpener::MasterFileRead, this, &TabWidget::UpdateSummary);

    connect(videoPlayer->GetPlayer(),&QMediaPlayer::durationChanged,timelineWid->GetToolBar(), &TimelineToolBar::ZoomOutTriggered);
    connect(videoPlayer->GetPlayer(),&QMediaPlayer::durationChanged,timelineWid->GetToolBar(), &TimelineToolBar::VolumeUpTriggered);


    //populate activity list
    connect(timelineWid->GetTimeline(), &Timeline::AddedActivity, activity, &ActivityList::AddActivityInList);
    connect(timelineWid->GetTimeline(), &Timeline::FlushedActivities, activity, &ActivityList::FlushActivities);
    connect(activity, &ActivityList::DoubleClicked, timelineWid->GetTimeline(), &Timeline::UpdateTimeline);
    connect(activity, &ActivityList::Clicked , inspector, &Inspector::SelectText);
    //control visibility nodes in timeline
    connect(timelineWid->GetToolBar(), &TimelineToolBar::VisibilitySwitch, timelineWid->GetTimeline(), &Timeline::UpdateTimeline);


}

TabWidget::~TabWidget(){
    delete this;
}

void TabWidget::UpdateSummary(){

    QApplication::setOverrideCursor(Qt::WaitCursor);
        summary->SetText(fo);

        QApplication::restoreOverrideCursor();
}

void TabWidget::OpenVideo(QString _fileName, int _fileNum){
    if(tabNum==_fileNum){
        videoPlayer->AddVideoInCombo(_fileName);
    }

}

void TabWidget::ZoomVideoCoord(){
    float videoPosition = videoPlayer->GetPlayer()->position();
    emit ZoomVideoCoordinator(videoPosition);
}

QString* TabWidget::GetName(){
    return &tabName;
}

void TabWidget::SetWidgetDimention(MainWindow* _mainWin){
    //todo-debug: on resize di window chiamare la funzione per aggiornare dimensione dei widget
    int  colWidth=  _mainWin->size().width()*0.98;
    int  rowHeight= _mainWin->size().height();

    leftColumnWidth = colWidth/6;
    centralColumnWidth = colWidth/6*2;
    rightColumnMinWidth  = colWidth/6*2.9;
    upperRowHeight = rowHeight/2 *0.8;
}
