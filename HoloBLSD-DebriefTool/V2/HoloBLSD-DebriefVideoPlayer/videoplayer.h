#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include "qboxlayout.h"
#include "qlabel.h"
#include "qslider.h"
#include <QObject>
#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>

class VideoPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit VideoPlayer(QWidget *parent = nullptr);

    void SetVideoLabel(QString _title);
    VideoPlayer(QWidget *parent, QString _name, int _width, int _height);
    ~VideoPlayer();
    void ShowVideo(QString _fileName);
    QMediaPlayer *GetPlayer();
    QSlider *GetSlider();
private:

    QBoxLayout* localLayout;
    QWidget* localWidget;
    QMediaPlayer* player;
    QVideoWidget* videoArea;
    QLabel* videoLabel;
    QSlider* videoSlider;
signals:

};

#endif // VIDEOPLAYER_H
