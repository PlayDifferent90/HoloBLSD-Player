#ifndef TIMELINETOOLBAR_H
#define TIMELINETOOLBAR_H

#include "fileopener.h"
#include "qicon.h"
#include "qaction.h"
#include "qlabel.h"
#include "qpushbutton.h"
#include "qslider.h"
#include <QObject>
#include <QWidget>

class TimelineToolBar : public QWidget
{
    Q_OBJECT
public:
    explicit TimelineToolBar(QObject *parent = nullptr);
    TimelineToolBar(QWidget *parent, FileOpener *_fo);
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
    const QIcon visibilityIcon = QIcon(":/Icons/VideoIcon/Invisibility_lightgrey.png");
    QPushButton* playButton;
    QPushButton* pauseButton;
    QPushButton* stopButton;
    QPushButton* volumeUpButton;
    QPushButton* volumeDownButton;
    QPushButton* volumeMuteButton;
    QPushButton* zoomInButton;
    QPushButton* zoomOutButton;
    QLabel* userVisiblity;
    QSlider* volumeSlider;
    QSlider* zoomSlider;
    FileOpener* fileOpener;
    int volume=0;
    int zoom=0;

signals:
    void Play();
    void Pause();
    void Stop();
    void Volume(int _vol);
    void VolumeMute();
    void Zoom(int _zoom);
    void VisibilitySwitch();
private:
    int SliderValueCheck(int _value);
    void NodeVisibilitySwitch(QString _name);
};

#endif // TIMELINETOOLBAR_H
