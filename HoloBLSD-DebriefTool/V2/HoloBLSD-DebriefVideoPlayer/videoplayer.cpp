#include "videoplayer.h"

VideoPlayer::VideoPlayer(QWidget *parent, FileOpener* _fo, int _width, int _height)
    : QWidget{parent}
{
    videoArea = new QVideoWidget(this);
    videoArea->setMinimumSize(_width, _height/10*8);
    videoArea->setMaximumSize(_width, _height/10*8);
    videoArea->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    videoLabel = new QLabel("Video:");
    videoLabel->setMaximumSize(_width,_height/10);

    player = new QMediaPlayer(this);
    player->setVideoOutput(videoArea);
    player->setNotifyInterval(500);

    videoCombo = new QComboBox(this);
    videoCombo->setMaximumWidth(_width);
    connect(videoCombo, &QComboBox::currentTextChanged, this, &VideoPlayer::ShowVideo);

    videoSlider = new QSlider(this);
    videoSlider->setOrientation(Qt::Horizontal);
    videoSlider->setMaximumHeight(_height/30);

    localLayout = new QVBoxLayout(this);
    localLayout->addWidget(videoLabel);
    localLayout->addWidget(videoCombo);
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
    connect(videoSlider,&QSlider::sliderMoved,player,&QMediaPlayer::setPosition);

}

VideoPlayer::~VideoPlayer(){
    delete this;
}

void VideoPlayer::AddVideoInCombo(QString _fileName){
    videoCombo->addItem(_fileName);
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
