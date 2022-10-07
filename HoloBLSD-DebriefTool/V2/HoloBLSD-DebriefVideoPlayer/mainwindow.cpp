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
   filename = QFileDialog::getOpenFileName(this,"Open a Log file","","(*.log *.txt)"); // check goodness file  --> might use VLC embedded in QT (QTVLC) // open cv
   if(filename !=""){

       QString userName = "User" + QString::number( users.length()+1);// todo: leggere da log
       fo = new FileOpener( userName);
       files.append(filename);
       users.append(userName);
       TabWidget* newTab = new TabWidget(this,userName,fo,files.length());
       mainTab->addTab(newTab, userName);

       fo->OpenLog(filename);

       emit userAdded(userName, files.length());
       emit videoAdded(filename,files.length());

       if(files.length()>1){
           CreateMasterTab();
           //do it once, then repopulate
       }
   }
}


FileOpener* MainWindow::GetFileOpener(){
    return fo;
}

void MainWindow::CreateMasterTab(){
    QString userName = "Master";// todo: leggere da log
    fo = new FileOpener( userName);

    TabWidget* newTab = new TabWidget(this,userName,fo,0);  //0= master
    mainTab->addTab(newTab, userName);

    fo->OpenLogMaster(files);

    emit userAdded(userName,0);
    emit videoAdded(filename, 0);  //todo: soluzione temporaneea, si dovranno poi associare più video e consenire di scegliere trai video
    foreach (QString s, users) {
        emit userAdded(s, 0);
    }
    mainTab->tabBar()->moveTab(files.length(),0);
}
