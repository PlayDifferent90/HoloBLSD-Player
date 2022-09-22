#include "timelinewidget.h"

TimelineWidget::TimelineWidget(QWidget *parent,FileOpener* _fileOpener ,int _width, int _height)
    : QWidget{parent}
{
    Theme* theme = new Theme();

    toolbarArea = new QScrollArea(this);
    toolbarArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    toolbarArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    toolbarArea->setFixedSize(_width,_height/15);
    toolbar = new TimelineToolBar(toolbarArea);
    qDebug()<<toolbarArea->actions();



    QScrollArea* localScrollArea = new QScrollArea(this);
    localScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    localScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    localScrollArea->setFixedSize(_width,_height);


    QVBoxLayout* timelineFrame = new QVBoxLayout(this);
    timelineFrame->setMargin(0);
    timelineFrame->addWidget(toolbarArea);
    timelineFrame->addWidget(localScrollArea);

    QHBoxLayout* timelineWidgetLayout = new QHBoxLayout(localScrollArea);

    QScrollArea* activityScrollArea = new QScrollArea();
    activityScrollArea->setMaximumWidth(_width/6);
    activityScrollArea->setMinimumWidth(_width/6);
    activityScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    activityScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    timelineWidgetLayout->addWidget(activityScrollArea);


    timelineScene = new QGraphicsScene();
    timelineView = new QGraphicsView(timelineScene);
    timelineView->setInteractive(true);

    timelineScene->setBackgroundBrush(theme->BGTEst);
    timelineScene->setSceneRect(0,0, 20000,1500);  // todo: calcoalre dimensioni da numero di activity, e durata tempo
    timelineWidgetLayout->addWidget(timelineView);

    timeline = new Timeline(timelineView,this, _fileOpener, 0);// todo : replace with videolength

    activityScene = new QGraphicsScene();
    activityView = new QGraphicsView(activityScene);
    activityView->setInteractive(true);

    activityScene->setBackgroundBrush(theme->BGTEst);
    activityScene->setSceneRect(0,0,_width/6,1000);
    DrawBackground(activityScene, _width/6,timeline->timelineNodeHeight/* *num of nodes */);
    activityScrollArea->setWidget(activityView);

    connect(activityScrollArea->verticalScrollBar(), &QScrollBar::valueChanged, timelineView->verticalScrollBar(), &QScrollBar::setValue);
    connect(timelineView->verticalScrollBar(),&QScrollBar::valueChanged, activityScrollArea->verticalScrollBar(), &QScrollBar::setValue);

}

void TimelineWidget::DrawBackground(QGraphicsScene* _scene, int _width, int _height){
    for (int i =1;i<100;i+=2){
        _scene->addRect(0,_height*i,_width,_height);
        //todo: add text
    }
}

Timeline* TimelineWidget::GetTimeline(){
    return timeline;
}

TimelineToolBar* TimelineWidget::GetToolBar(){
    return toolbar;
}

