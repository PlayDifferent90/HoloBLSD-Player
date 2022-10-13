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
   QFileInfo fileInfo(filename);
   if(filename !=""){

       QString userName = fileInfo.baseName();
       fo = new FileOpener( userName);
       files.append(filename);
       users.append(userName);
       QApplication::setOverrideCursor(Qt::WaitCursor);

       TabWidget* newTab = new TabWidget(this,userName,fo,files.length());
       mainTab->addTab(newTab, userName);

       fo->OpenLog(filename);

       emit userAdded(userName, files.length());
       emit videoAdded(filename,files.length());


       if(files.length()>1){
           if(files.length()>2){
               mainTab->removeTab(0);
           }
           CreateMasterTab();
       }

       QApplication::restoreOverrideCursor();
   }
}


FileOpener* MainWindow::GetFileOpener(){
    return fo;
}

void MainWindow::CreateMasterTab(){
    QString userName = "Master";
    fo = new FileOpener( userName);
    fo->SetUsersList(users);

    TabWidget* newTab = new TabWidget(this,userName,fo,0);  //0= master


    fo->OpenLogMaster(files);

    mainTab->addTab(newTab, userName);


    emit userAdded(userName,0);
    emit videoAdded(filename, 0);  //todo: soluzione temporaneea, si dovranno poi associare più video e consenire di scegliere trai video
    foreach (QString s, users) {
        emit userAdded(s, 0);
    }
    mainTab->tabBar()->moveTab(files.length(),0);
    mainTab->setTabIcon(0,masterIcon);
}

void MainWindow::on_actionOpen_File_triggered()
{
    on_actionOpenSingleUserFile_triggered();
}

void MainWindow::SaveTimelineValues(float _scale, float _volume, float _videoC){
    scale=_scale;
    volume=_volume;
    videoCursor=_videoC;
}

void MainWindow::on_actionOpen_Session_triggered()
{
    //Apre salvataggio
}



void MainWindow::on_actionSave_Session_triggered()
{
    emit SaveSession();

    QString sessionName = QFileDialog::getSaveFileName(this,
        tr("Save Debrief Session"), "",
        tr("Debrief Session (*.txt);;All Files (*)"));

    if (sessionName.isEmpty())
         return;
     else {QFile file(sessionName);
        if(!file.open(QIODevice::OpenModeFlag::ReadWrite)){
            qCritical()<<"can't open file";
            return;
        }
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_4_5);
        out << QString::number(scale)<<",";
        out << QString::number(volume)<<",";
        out << QString::number(videoCursor)<<"\n";
        foreach (QString s, files) {
            out << s <<"\n";
        }
        foreach(Activity* a, fo->GetActivities()){
            out<< QString::number(a->GetActID()) <<","<<QString::number(a->GetVisibility())<<"\n";
        }
        file.flush();
    }
}


void MainWindow::on_actionPlay_triggered()
{
    emit Play();
}


void MainWindow::on_actionPause_triggered()
{
    emit Pause();
}


void MainWindow::on_actionStop_triggered()
{
    emit Stop();
}


void MainWindow::on_actionVolume_Down_triggered()
{
    emit VolumeD();
}


void MainWindow::on_actionVolume_Up_triggered()
{
    emit VolumeU();
}


void MainWindow::on_actionVolume_Mute_triggered()
{
    emit VolumeM();
}


void MainWindow::on_actionZoomIn_triggered()
{
    emit ZoomI();
}


void MainWindow::on_actionZoomOut_triggered()
{
    emit ZoomO();
}

