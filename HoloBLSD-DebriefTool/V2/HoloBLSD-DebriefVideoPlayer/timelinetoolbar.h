#ifndef TIMELINETOOLBAR_H
#define TIMELINETOOLBAR_H

#include "fileopener.h"
#include "mainwindow.h"
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
    TimelineToolBar(QWidget *parent, FileOpener *_fo, MainWindow* mainwin);
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

    const QIcon playIcon = QIcon(":/Icons/VideoIcon/VideoPlay_white.png");
    const QIcon pauseIcon = QIcon(":/Icons/VideoIcon/VideoPause_white.png");
    const QIcon stopIcon = QIcon(":/Icons/VideoIcon/VideoStop_white.png");
    const QIcon volumeUpIcon = QIcon(":/Icons/VideoIcon/VolumeUp_white.png");
    const QIcon volumeDownIcon = QIcon(":/Icons/VideoIcon/VolumeDown_white.png");
    const QIcon volumeMuteIcon = QIcon(":/Icons/VideoIcon/VolumeMute_white.png");
    const QIcon zoomInIcon = QIcon(":/Icons/VideoIcon/ZoomIn_white.png");
    const QIcon zoomOutIcon = QIcon(":/Icons/VideoIcon/ZoomOut_white.png");
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
