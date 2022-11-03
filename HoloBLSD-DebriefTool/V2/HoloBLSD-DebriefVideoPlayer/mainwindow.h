#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QDebug>
#include <QTimer>
#include "fileopener.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    FileOpener* GetFileOpener();

    void SaveTimelineValues(int _scale, int _volume, int _videoC);
    int GetScale();
    int GetVolume();
    int GetVC();
private slots:
    void on_actionOpenSingleUserFile_triggered();
    void on_actionOpen_File_triggered();

    void on_actionOpen_Session_triggered();

    void on_actionStop_triggered();

    void on_actionSave_Session_triggered();

    void on_actionPlay_triggered();

    void on_actionPause_triggered();

    void on_actionVolume_Down_triggered();

    void on_actionVolume_Up_triggered();

    void on_actionVolume_Mute_triggered();

    void on_actionZoomIn_triggered();

    void on_actionZoomOut_triggered();

    void on_actionNew_Session_triggered();

private:
    Ui::MainWindow *ui;
    QString startUpTabName = "Empty";
    QTabWidget* mainTab;
    QList<QString> users;
    QList<QString> files;
    FileOpener* fo;
    QString filename;
    int videoCursor,scale,volume;
    const QIcon masterIcon = QIcon(":/Icons/VideoIcon/master_white.png");
    const QIcon alarmIcon = QIcon(":/Icons/VideoIcon/alarm.png");
    const QString alarmTitle= "Opening  New Session";
    const QString alarmText= "Opening a new session will result in losing  the current open session.\n Do yo want to save your progress?";
    void CreateMasterTab();
    void UpdateMasterTab();

    void OpenFile(QString filename);
signals:
    void userAdded(QString _userName, int tabID);
    void videoAdded(QString _fileName, int tabID);
    void Play();
    void Pause();
    void Stop();
    void VolumeD();
    void VolumeU();
    void VolumeM();
    void ZoomI();
    void ZoomO();
    void SaveSession();
    void OpenSession();
};
#endif // MAINWINDOW_H
