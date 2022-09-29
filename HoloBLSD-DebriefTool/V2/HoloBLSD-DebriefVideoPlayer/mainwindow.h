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
    void on_actionOpenVideo_triggered();

    void on_actionOpenSingleUserFile_triggered();

    void on_actionAddActvity_triggered();


    void on_actionOpenFile_triggered();

private:
    Ui::MainWindow *ui;
    void NewTab(QString _name, FileOpener *_fileOpener);
    QString startUpTabName = "Empty";
    QTabWidget* mainTab;
    QAction* demoAction;
    QList<QString> users;
    FileOpener* fo;
signals:
    void userAdded(QString _userName);
    void videoAdded(QString _fileName);
    void addActivity(QString actName);
};
#endif // MAINWINDOW_H
