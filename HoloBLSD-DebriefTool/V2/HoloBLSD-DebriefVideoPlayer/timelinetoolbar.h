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
#include <QComboBox>

class TimelineToolBar : public QWidget
{
    Q_OBJECT
public:
    explicit TimelineToolBar(QObject *parent = nullptr);
    TimelineToolBar(QWidget *parent, FileOpener *_fo, MainWindow* mainwin, int _wid, int _hei);
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
    void VisibilitySwitch(QString selected);

    const QIcon playIcon = QIcon(":/Icons/VideoIcon/VideoPlay_white.png");
    const QIcon pauseIcon = QIcon(":/Icons/VideoIcon/VideoPause_white.png");
    const QIcon stopIcon = QIcon(":/Icons/VideoIcon/VideoStop_white.png");
    const QIcon volumeUpIcon = QIcon(":/Icons/VideoIcon/VolumeUp_white.png");
    const QIcon volumeDownIcon = QIcon(":/Icons/VideoIcon/VolumeDown_white.png");
    const QIcon volumeMuteIcon = QIcon(":/Icons/VideoIcon/VolumeMute_white.png");
    const QIcon zoomInIcon = QIcon(":/Icons/VideoIcon/ZoomIn_white.png");
    const QIcon zoomOutIcon = QIcon(":/Icons/VideoIcon/ZoomOut_white.png");
    const QIcon visible = QIcon(":/Icons/VideoIcon/Visibility_gold.png");
    const QIcon invisible = QIcon(":/Icons/VideoIcon/InvisibilityClosed_gold.png");
    QPushButton* playButton;
    QPushButton* pauseButton;
    QPushButton* stopButton;
    QPushButton* volumeUpButton;
    QPushButton* volumeDownButton;
    QPushButton* volumeMuteButton;
    QPushButton* zoomInButton;
    QPushButton* zoomOutButton;
    QComboBox* userCombo;
    QLabel* userVisiblity;
    QSlider* volumeSlider;
    QSlider* zoomSlider;
    FileOpener* fileOpener;
    int volume=0;
    int zoom=0;
    int selectedNumber = 0;
    QString placeHolder = " Select User..."; // tohave better visualization in mmenuu

    void SetZoom(int _zoom);
    void SetVolume(int _volume);
signals:
    void Play();
    void Pause();
    void Stop();
    void Volume(int _vol);
    void VolumeMute();
    void Zoom(int _zoom);
  //  void NodeVisibilitySwitch(QString _name);
private:
    int SliderValueCheck(int _value);
};

#endif // TIMELINETOOLBAR_H
