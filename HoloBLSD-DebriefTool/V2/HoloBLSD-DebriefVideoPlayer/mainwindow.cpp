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


void MainWindow::on_actionOpenSingleUserFile_triggered()
{
   QString filename = QFileDialog::getOpenFileName(this,"Open a Log file","","(*.*)"); // check goodness file  --> might use VLC embedded in QT (QTVLC) // open cv
   QString userName = "Ugo User";// todo: leggere da log
   fo = new FileOpener( userName);
   files.append(fo);

   TabWidget* newTab = new TabWidget(this,userName,fo,files.length());
   mainTab->addTab(newTab, userName);

   fo->OpenLog(filename);

   emit userAdded(userName, files.length());
   emit videoAdded(filename,files.length());
}


FileOpener* MainWindow::GetFileOpener(){
    return fo;
}
