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

private:
    Ui::MainWindow *ui;
    QString startUpTabName = "Empty";
    QTabWidget* mainTab;
    QAction* demoAction;
    QList<QString> users;
    QList<QString> files;
    FileOpener* fo;
    QString filename;
    void CreateMasterTab();
    void UpdateMasterTab();
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
};
#endif // MAINWINDOW_H
