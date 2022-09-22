#include "videoplayer.h"

VideoPlayer::VideoPlayer(QWidget *parent, QString _name, int _width, int _height)
    : QWidget{parent}
{
    //todo set window larger
    videoArea = new QVideoWidget(this);
    videoArea->setMinimumSize(_width, _height/5*4.5);
    videoArea->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    player = new QMediaPlayer(this);
    player->setVideoOutput(videoArea);

    videoLabel = new QLabel(this);
    videoLabel->setMaximumHeight(_height/50);
    SetVideoLabel(_name);

    videoSlider = new QSlider(this);
    videoSlider->setOrientation(Qt::Horizontal);
    videoSlider->setMaximumHeight(_height/30);

    localLayout = new QVBoxLayout(this);
    localLayout->addWidget(videoLabel);
    localLayout->addWidget(videoArea);
    localLayout->addWidget(videoSlider);

    localWidget = new QWidget(this);
    localWidget->setLayout(localLayout);
    localWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    //localWidget->setMinimumSize(_width, _height);
    // durata video -> lunghezza barra
    connect(player,&QMediaPlayer::durationChanged,videoSlider,&QSlider::setMaximum);
    // riproduzione video -> scorrimento barra
    connect(player,&QMediaPlayer::positionChanged,videoSlider,&QSlider::setValue);
    //scorrimento barra -> riproduzione video
    connect(videoSlider,&QSlider::sliderMoved,player,&QMediaPlayer::setPosition); // todo: works with int64, better to calcualte percentage outside

}

VideoPlayer::~VideoPlayer(){
    delete this;
}

void VideoPlayer::SetVideoLabel(QString _title){
    videoLabel->setText(_title);
}

void VideoPlayer::ShowVideo(QString _fileName){
    player->setMedia(QUrl::fromLocalFile(_fileName.left(_fileName.lastIndexOf("."))+ extention));

    player->play();
    player->pause();
}
QMediaPlayer* VideoPlayer::GetPlayer(){
    return player;
}
QSlider* VideoPlayer::GetSlider(){
    return videoSlider;
}
