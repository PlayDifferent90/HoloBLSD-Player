#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tabwidget.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setMinimumSize(1080,720);
    ui->setupUi(this);

     //Add main tab widget to main window
    mainTab = new QTabWidget(parent);
    ui->horizontalLayout->addWidget(mainTab);
    QTimer::singleShot(0, this, SLOT(showMaximized()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NewTab(QString _name,FileOpener* _fileOpener){
    TabWidget* newTab = new TabWidget(this,_name,_fileOpener);
    mainTab->addTab(newTab, _name);

}

void MainWindow::on_actionOpenVideo_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Open a file","","(*.*)"); // check goodness file  --> might use VLC embedded in QT (QTVLC) // open cv
    emit videoAdded(fileName);
}

void MainWindow::on_actionOpenSingleUserFile_triggered()
{
   QString filename = QFileDialog::getOpenFileName(this,"Open a Log file","","(*.*)"); // check goodness file  --> might use VLC embedded in QT (QTVLC) // open cv
   QString userName = "Ugo User";// todo: leggere da log
   fo = new FileOpener( userName);
   NewTab(userName, fo);
   fo->OpenLog(filename);

   emit userAdded(userName);
   emit videoAdded(filename);
}

void MainWindow::on_actionAddActvity_triggered(){
    emit addActivity("newAct");
}

void MainWindow::on_actionOpenFile_triggered()
{
}

FileOpener* MainWindow::GetFileOpener(){
    return fo;
}
