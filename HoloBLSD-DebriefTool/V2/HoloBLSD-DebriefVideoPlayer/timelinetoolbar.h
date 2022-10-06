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

    const QIcon playIcon = QIcon(":/Icons/VideoIcon/VideoPlay.png");
    const QIcon pauseIcon = QIcon(":/Icons/VideoIcon/VideoPause.png");
    const QIcon stopIcon = QIcon(":/Icons/VideoIcon/VideoStop.png");
    const QIcon volumeUpIcon = QIcon(":/Icons/VideoIcon/VolumeUp.png");
    const QIcon volumeDownIcon = QIcon(":/Icons/VideoIcon/VolumeDown.png");
    const QIcon volumeMuteIcon = QIcon(":/Icons/VideoIcon/VolumeMute.png");
    const QIcon zoomInIcon = QIcon(":/Icons/VideoIcon/ZoomIn.png");
    const QIcon zoomOutIcon = QIcon(":/Icons/VideoIcon/ZoomOut.png");
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
