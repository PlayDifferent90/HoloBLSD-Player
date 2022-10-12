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
};
#endif // MAINWINDOW_H
