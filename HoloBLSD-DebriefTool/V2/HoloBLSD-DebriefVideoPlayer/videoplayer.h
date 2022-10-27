#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include "qboxlayout.h"
#include "qlabel.h"
#include "qslider.h"
#include <QObject>
#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include "fileopener.h"
#include "QComboBox.h"

class VideoPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit VideoPlayer(QWidget *parent = nullptr);

    VideoPlayer(QWidget *parent, FileOpener* _fo, int _width, int _height);
    ~VideoPlayer();
    void ShowVideo(QString _fileName);
    QMediaPlayer *GetPlayer();
    QSlider *GetSlider();
    void AddVideoInCombo(QString _fileName);
private:
    FileOpener* fo;
    QBoxLayout* localLayout;
    QWidget* localWidget;
    QMediaPlayer* player;
    QVideoWidget* videoArea;
    QComboBox* videoCombo;
    QLabel* videoLabel;
    QSlider* videoSlider;
    QString extention = ".mp4";
signals:

};

#endif // VIDEOPLAYER_H
