#ifndef TIMELINETOOLBAR_H
#define TIMELINETOOLBAR_H

#include "qicon.h"
#include "qaction.h"
#include "qpushbutton.h"
#include "qslider.h"
#include <QObject>
#include <QWidget>

class TimelineToolBar : public QWidget
{
    Q_OBJECT
public:
    explicit TimelineToolBar(QObject *parent = nullptr);
    TimelineToolBar(QWidget *parent);
    void PlayTriggered();
    void PauseTriggered();
    void StopTriggered();
    void VolumeUpTriggered();
    void VolumeDownTriggered();
    void VolumeMuteTriggered();
    void VolumeValue();
    void ZoomInTriggered();
    void ZoomOutTriggered();
    void ZoomValue();

    const QIcon playIcon = QIcon(":/VideoIcon/VideoPlay.png");
    const QIcon pauseIcon = QIcon(":/VideoIcon/VideoPlay.png");
    const QIcon stopIcon = QIcon(":/VideoIcon/VideoPlay.png");
    const QIcon volumeUpIcon = QIcon(":/VideoIcon/VideoPlay.png");
    const QIcon volumeDownIcon = QIcon(":/VideoIcon/VideoPlay.png");
    const QIcon volumeMuteIcon = QIcon(":/VideoIcon/VideoPlay.png");
    const QIcon zoomInIcon = QIcon(":/VideoIcon/VideoPlay.png");
    const QIcon zoomOutIcon = QIcon(":/VideoIcon/VideoPlay.png");
    QPushButton* playButton;
    QPushButton* pauseButton;
    QPushButton* stopButton;
    QPushButton* volumeUpButton;
    QPushButton* volumeDownButton;
    QPushButton* volumeMuteButton;
    QPushButton* zoomInButton;
    QPushButton* zoomOutButton;
    QSlider* volumeSlider;
    QSlider* zoomSlider;
    int volume=0;
    int zoom=0;


signals:
    void Play();
    void Pause();
    void Stop();
    void Volume(int _vol);
    void VolumeMute();
    void Zoom(int _zoom);
private:
    int SliderValueCheck(int _value);
};

#endif // TIMELINETOOLBAR_H
