#include "timelinetoolbar.h"
#include "qapplication.h"
#include "uservisibilitybutton.h"
#include "qboxlayout.h"
#include "qdebug.h"

TimelineToolBar::TimelineToolBar(QWidget *parent, FileOpener* _fo, MainWindow* mainWin, int _wid, int _hei)
    : QWidget{parent}
{
    fileOpener=_fo;

    QHBoxLayout* layout = new QHBoxLayout(parent);
    //play, pause, stop
    playButton = new QPushButton(playIcon,"",this);
    connect(playButton, &QPushButton::pressed, this, &TimelineToolBar::PlayTriggered);

    pauseButton = new QPushButton(pauseIcon,"",this);
    connect(pauseButton, &QPushButton::pressed, this, &TimelineToolBar::PauseTriggered);

    stopButton = new QPushButton(stopIcon,"",this);
    connect(stopButton, &QPushButton::pressed, this, &TimelineToolBar::StopTriggered);

    //volume
    volumeUpButton = new QPushButton(volumeUpIcon,"",this);
    connect(volumeUpButton, &QPushButton::pressed, this, &TimelineToolBar::VolumeUpTriggered);

    volumeDownButton = new QPushButton(volumeDownIcon,"",this);
    connect(volumeDownButton, &QPushButton::pressed, this, &TimelineToolBar::VolumeDownTriggered);

    volumeMuteButton = new QPushButton(volumeMuteIcon,"",this);
    connect(volumeMuteButton, &QPushButton::pressed, this, &TimelineToolBar::VolumeMuteTriggered);

    volumeSlider = new QSlider(Qt::Horizontal, this);
    connect(volumeSlider, &QSlider::sliderMoved,this, &TimelineToolBar::VolumeValue);
    volumeSlider->setMaximumWidth(_wid/6);

    //zoom
    zoomInButton = new QPushButton(zoomInIcon,"",this);
    connect(zoomInButton, &QPushButton::pressed, this, &TimelineToolBar::ZoomInTriggered);

    zoomOutButton = new QPushButton(zoomOutIcon,"",this);
    connect(zoomOutButton, &QPushButton::pressed, this, &TimelineToolBar::ZoomOutTriggered);

    zoomSlider = new QSlider(Qt::Horizontal, this);
    connect(zoomSlider, &QSlider::sliderMoved,this, &TimelineToolBar::ZoomValue);
    zoomSlider->setSliderPosition(100);
    zoomSlider->setMaximumWidth(_wid/6);

    //visibility
    QList<QString> users = _fo->GetUsersList();
    if(users.length()>0){
        userCombo = new QComboBox(this);
        userCombo->setMinimumSize(_wid/6,_hei/2);
        userCombo->setMaximumSize(_wid/6,_hei/2);
        layout->addWidget(userCombo);

        userCombo->addItem(placeHolder);
        foreach(QString user, users ){
                    userCombo->addItem(visible, user);
                }
       connect(userCombo, &QComboBox::currentTextChanged, this, &TimelineToolBar::VisibilitySwitch);
    }else{
        layout->addSpacing(_wid/6);
    }
    layout->addWidget(zoomOutButton);
    layout->addWidget(zoomSlider);
    layout->addWidget(zoomInButton);
    layout->addSpacing(_wid/6*5/6);//dinamic sizechange
    layout->addWidget(playButton);
    layout->addWidget(pauseButton);
    layout->addWidget(stopButton);
    layout->addSpacing(_wid/6*7/6);//dinamic sizechange
    layout->addWidget(volumeMuteButton);
    layout->addWidget(volumeDownButton);
    layout->addWidget(volumeSlider);
    layout->addWidget(volumeUpButton);


    connect(mainWin, &MainWindow::ZoomI, this, &TimelineToolBar::ZoomInTriggered);
    connect(mainWin, &MainWindow::ZoomO, this, &TimelineToolBar::ZoomOutTriggered);

    connect(mainWin, &MainWindow::Play, this, &TimelineToolBar::PlayTriggered);
    connect(mainWin, &MainWindow::Pause, this, &TimelineToolBar::PauseTriggered);
    connect(mainWin, &MainWindow::Stop, this, &TimelineToolBar::StopTriggered);


    connect(mainWin, &MainWindow::VolumeD, this, &TimelineToolBar::VolumeDownTriggered);
    connect(mainWin, &MainWindow::VolumeU, this, &TimelineToolBar::VolumeUpTriggered);
    connect(mainWin, &MainWindow::VolumeM, this, &TimelineToolBar::VolumeMuteTriggered);

 }

void TimelineToolBar::VisibilitySwitch(QString selected){
   if(selected!=placeHolder){
       foreach(Activity* act, fileOpener->GetActivities()){
           foreach(Node* n, act->GetNodes()){
               if(n->GetUserID()==selected){
                   n->NodeSwitch();
                   if(n->IsVisible()){
                       //cambiare icona conta come cambio testo -> loop infinito
                       userCombo->blockSignals(true);
                       userCombo->setItemIcon(userCombo->currentIndex(),visible);
                       userCombo->blockSignals(false);
                   } else{
                       userCombo->blockSignals(true);
                       userCombo->setItemIcon(userCombo->currentIndex(),invisible);
                       userCombo->blockSignals(false);
                   }
                   emit Zoom(zoom);
               }
           }
       }
       userCombo->setCurrentIndex(0);
   }
}

void TimelineToolBar::SetZoom(int _zoom){
    zoom=_zoom;
}

void TimelineToolBar::SetVolume(int _volume){
    volume=_volume;
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
