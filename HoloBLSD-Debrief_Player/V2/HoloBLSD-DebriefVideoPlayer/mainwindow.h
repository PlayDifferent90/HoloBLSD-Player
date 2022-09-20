#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QDebug>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpenVideo_triggered();

    void on_actionOpenSingleUserFile_triggered();

    void on_actionAddActvity_triggered();

    void on_actionPlay_triggered();

private:
    Ui::MainWindow *ui;
    void NewTab(QString _name);
    QString startUpTabName = "Empty";
    QTabWidget* mainTab;
    QAction* demoAction;
    QList<QString> users;
signals:
    void userAdded(QString _userName);
    void videoAdded(QString _fileName);
    void addActivity(QString actName);
};
#endif // MAINWINDOW_H
