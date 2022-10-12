#include "timelinetoolbar.h"
#include "qapplication.h"
#include "uservisibilitybutton.h"
#include "qboxlayout.h"
#include "qdebug.h"

TimelineToolBar::TimelineToolBar(QWidget *parent, FileOpener* _fo)
    : QWidget{parent}
{
    fileOpener=_fo;

    QHBoxLayout* layout = new QHBoxLayout(parent);
    layout->setMargin(0);;

    //play, pause, stop
    playButton = new QPushButton(playIcon,"Play",this);
    connect(playButton, &QPushButton::pressed, this, &TimelineToolBar::PlayTriggered);

    pauseButton = new QPushButton(pauseIcon,"Pause",this);
    connect(pauseButton, &QPushButton::pressed, this, &TimelineToolBar::PauseTriggered);

    stopButton = new QPushButton(stopIcon,"Stop",this);
    connect(stopButton, &QPushButton::pressed, this, &TimelineToolBar::StopTriggered);

    //volume
    volumeUpButton = new QPushButton(volumeUpIcon,"volumeUp",this);
    connect(volumeUpButton, &QPushButton::pressed, this, &TimelineToolBar::VolumeUpTriggered);

    volumeDownButton = new QPushButton(volumeDownIcon,"volumeDown",this);
    connect(volumeDownButton, &QPushButton::pressed, this, &TimelineToolBar::VolumeDownTriggered);

    volumeMuteButton = new QPushButton(volumeMuteIcon,"volumeMute",this);
    connect(volumeMuteButton, &QPushButton::pressed, this, &TimelineToolBar::VolumeMuteTriggered);

    volumeSlider = new QSlider(Qt::Horizontal, this);
    connect(volumeSlider, &QSlider::sliderMoved,this, &TimelineToolBar::VolumeValue);

    //zoom
    zoomInButton = new QPushButton(zoomInIcon,"zoomIn",this);
    connect(zoomInButton, &QPushButton::pressed, this, &TimelineToolBar::ZoomInTriggered);

    zoomOutButton = new QPushButton(zoomOutIcon,"zoomOut",this);
    connect(zoomOutButton, &QPushButton::pressed, this, &TimelineToolBar::ZoomOutTriggered);

    zoomSlider = new QSlider(Qt::Horizontal, this);
    connect(zoomSlider, &QSlider::sliderMoved,this, &TimelineToolBar::ZoomValue);
    zoomSlider->setSliderPosition(100);

    //visibility
    QList<QString> users = _fo->GetUsersList();
    if(users.length()>0){
        //textitem
        foreach(QString user, users ){
            qDebug()<<"creating button visibility";
            UserVisibilityButton* UB = new UserVisibilityButton(fileOpener,user,this);
            layout->addWidget(UB);
            connect(UB, &UserVisibilityButton::VisibilityPressed, this, &TimelineToolBar::VisibilitySwitch);
        }
    }
    layout->addSpacing(420);
    layout->addWidget(playButton);
    layout->addWidget(pauseButton);
    layout->addWidget(stopButton);
    layout->addSpacing(200);
    layout->addWidget(volumeMuteButton);
    layout->addWidget(volumeDownButton);
    layout->addWidget(volumeSlider);
    layout->addWidget(volumeUpButton);
    layout->addSpacing(400);
    layout->addWidget(zoomOutButton);
    layout->addWidget(zoomSlider);
    layout->addWidget(zoomInButton);

}


void TimelineToolBar::PlayTriggered(){
    qDebug()<<"play";
    emit Play();
}

void TimelineToolBar::PauseTriggered(){
    qDebug()<<"pause";
    emit Pause();
}
void TimelineToolBar::StopTriggered(){
    qDebug()<<"stop";
    emit Stop();
}

void TimelineToolBar::VolumeUpTriggered(){
    volume = SliderValueCheck(volume +5);
    qDebug()<<"volumeUp : " + QString::number(volume);
    volumeSlider->setSliderPosition(volume);
    VolumeValue();
}
void TimelineToolBar::VolumeDownTriggered(){
    volume = SliderValueCheck(volume -5);
    qDebug()<<"volumeDown : " + QString::number(volume);
    volumeSlider->setSliderPosition(volume);
    VolumeValue();
}
void TimelineToolBar::VolumeMuteTriggered(){
    volume =0;
    qDebug()<<"volumeMute : " + QString::number(volume);
    volumeSlider->setSliderPosition(volume);
    VolumeValue();
}
void TimelineToolBar::VolumeValue(){
    qDebug()<<"volume Value : " + QString::number(volume);
    volume = volumeSlider->sliderPosition();
    emit Volume(volume);
}

void TimelineToolBar::ZoomInTriggered(){

    QApplication::setOverrideCursor(Qt::WaitCursor);
    zoom = SliderValueCheck(zoom +5);
    qDebug()<<"zoomIn : " + QString::number(zoom);
    zoomSlider->setSliderPosition(zoom);
    ZoomValue();
    QApplication::restoreOverrideCursor();
}
void TimelineToolBar::ZoomOutTriggered(){

    QApplication::setOverrideCursor(Qt::WaitCursor);
    zoom = SliderValueCheck(zoom -5);
    qDebug()<<"zoomOut : " + QString::number(zoom);
    zoomSlider->setSliderPosition(zoom);
    ZoomValue();
    QApplication::restoreOverrideCursor();
}

void TimelineToolBar::ZoomValue(){
    qDebug()<<"zoom Value : " + QString::number(zoom);
    zoom = zoomSlider->sliderPosition();
    emit Zoom(zoom);
}

int TimelineToolBar::SliderValueCheck(int _value){
    if(_value <=0) return 1;
    else if(_value >=100) return 100;
    else return _value;
}
