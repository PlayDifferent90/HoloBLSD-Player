#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "activityentry.h"
#include <QAction>
#include <QDebug>
#include <QListIterator>
#include <QBuffer>
#include <QApplication>
#include <QMimeData>
#include <QGraphicsSceneHoverEvent>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    activityNodes = new QList<Activity>;

    /*Get UI*/
    ui->setupUi(this);

    videoLength = ui->scrollTimeLine->width();

    /*Setup Timeline Widget*/
    scene= new QGraphicsScene();

    viewTimeLine = new QGraphicsView(scene);
    timeline = new TimeLine(viewTimeLine);

    viewTimeLine->setInteractive(true);
    viewTimeLine->setMouseTracking(true);
    viewTimeLine->setFocus();

    /*Create Horizontal Line*/
    UpdateTimeLineLength(videoLength);

    /*Assign and Show timeline*/

    ui->scrollTimeLine->setWidget(viewTimeLine);
    ui->scrollTimeLine->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollTimeLine->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollTimeLine->setDisabled(true);

    ui->pushButtonZoomIn->setDisabled(true);
    ui->pushButtonZoomOut->setDisabled(true);
    ui->horizontalSliderZoom->setDisabled(true);

    ui->horizontalSliderZoom->setTickInterval(25);
    ui->horizontalSliderZoom->setTickPosition(QSlider::TicksAbove);
    ui->horizontalSliderZoom->setValue(50);

    /*Video Player*/

    player = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);
    player->setVideoOutput(videoWidget);
    videoWidget->setAspectRatioMode(Qt::KeepAspectRatio);

    slider = new QSlider(this);
    slider->setOrientation(Qt::Horizontal);

    ui->videoTools->addWidget(slider);
    ui->scrollArea_Video->setWidget(videoWidget);

    /*SLOTS AND SIGNALS*/
    // durata video -> lunghezza barra
    connect(player,&QMediaPlayer::durationChanged,slider,&QSlider::setMaximum);
    //durata video -> lunghezza timeline
    connect(player,&QMediaPlayer::durationChanged,timeline,&TimeLine::DrawTimeLineAxis);
    // riproduzione video -> scorrimento barra
    connect(player,&QMediaPlayer::positionChanged,slider,&QSlider::setValue);
    // riproduzione video -> scorrimento timeline
    connect(player,&QMediaPlayer::positionChanged,this,&MainWindow::MoveVideoCursor);

    //scorrimento barra -> riproduzione video
    connect(slider,&QSlider::sliderMoved,player,&QMediaPlayer::setPosition); // works with int64, better to calcualte percentage outside
    //scorrimento barra -> scorriemnto timeline
    connect(slider, &QSlider::sliderMoved,this,&MainWindow::MoveVideoCursor);

    //scorrimento timeline -> scorrimento barra
    connect(this,&MainWindow::SignalVideoCursor, slider, &QSlider::setValue);
    //scorrimento timeline -> riproduzione video
    connect(this,&MainWindow::SignalVideoCursor, player, &QMediaPlayer::setPosition);

    //prolungamento evento cursor moved
    connect (timeline->videoCursor, &VideoCursor::CursorMoved, this, &MainWindow::SlotVideoCursor);
    //adattamento iniziale schermata
    connect(player,&QMediaPlayer::durationChanged,this,&MainWindow::UpdateViewInit);

}

void MainWindow::PrintSignalDebug(){
    qDebug()<<"ping";
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*click su listactivities*/
void MainWindow::on_listWidgetActivities_itemClicked(QListWidgetItem *item)
{
   //select activity, display info in inspector and change graphic item color

}


void MainWindow::on_listWidgetActivities_itemDoubleClicked(QListWidgetItem *item)
{
    for(int a=0;a < activityNodes->length();a++){
        if(activityNodes->at(a).actListItemWidget->text()==item->text()){
            (*activityNodes)[a].visibilitySwitch();
        }
    }
    UpdateTimeLine(tlScale);

}


/*zoom timeline*/
void MainWindow::on_pushButtonZoomOut_clicked()
{
    tlScale*=0.9;

    if(tlScale<minScale) tlScale = minScale;
    if(tlScale<1.01 && tlScale > 1) tlScale = 1;
    UpdateTimeLine(tlScale);
    ui->horizontalSliderZoom->setValue(100*tlScale-1);
    qDebug()<<" " <<tlScale;
}

void MainWindow::on_pushButtonZoomIn_clicked()
{
    tlScale *= 1.1111;
    if(tlScale<1.01 && tlScale > 1) tlScale = 1;
    UpdateTimeLine(tlScale);
    ui->horizontalSliderZoom->setValue(100*tlScale-1);
    qDebug()<<" " <<tlScale;
}


void MainWindow::on_horizontalSliderZoom_sliderMoved(int position)
{
    float sliderValue = (float) (position+1)/100;
    tlScale =sliderValue;
    if(tlScale<minScale) tlScale = minScale;
    UpdateTimeLine(tlScale);
    qDebug()<<sliderValue <<" " <<tlScale;
}


//------------------------------------------------------------------------------------------todo: move to timeline
void MainWindow::UpdateTimeLineLength(float length)
{
    timeline->DrawTimeLineAxis(length);
}

void MainWindow::UpdateTimeLine(float scale){

    timeline->SetScale(tlScale);
    //timeline->videoCursor->SetScale(tlScale);
    timeline->FlushTimeLineElement();

    videoLength = player->duration();
    float scaledVideo = scaledVideoLength(videoLength,scale);
    UpdateTimeLineLength(scaledVideo);
    scene->setSceneRect(0,0,scaledVideo+1000,(actNum+1)*30); //(long term) 30-->timeline::heightrect

    int line =0;
    QList<QString> hiddenAct;
    foreach(Activity a, *activityNodes) {
        if(a.isVisible){
            if(a.isEvent){
                a.UpdateRectLength(tlScale);
                timeline->DrawEvent( a.UpdateStartingPoint(a.actID-line,tlScale));
            }else{
                a.UpdateRectLength(tlScale);
                timeline->DrawNode(a.nameAct, a.UpdateStartingPoint(a.actID-line,tlScale) , *a.actRect);
            }
        }else{
            if(!hiddenAct.contains(a.nameAct)){
                hiddenAct.append(a.nameAct);
                line=hiddenAct.length();
            }
        }
    }
}

float MainWindow::scaledVideoLength(float lineLength, float scale){

    //todo: fix control on width
    float actualTLL = lineLength*scale;
    int scrollTabWidth = ui->scrollTimeLine->viewport()->size().width();// width();



    if(actualTLL< scrollTabWidth){
        minScale = scale;
        return scrollTabWidth;
    }
    return actualTLL;
}

void MainWindow::UpdateViewInit(){
    videoLength = player->duration();

    while(tlScale!=minScale){
        on_pushButtonZoomOut_clicked();

    }
    ui->label_int3->setText(QDateTime::fromMSecsSinceEpoch(videoLength).toString("mm:ss"));  //todo: trovare fromula giusta


    DrawActivities();
}
//------------------------------------------------------------------------------------------todo: move to timeline

/*file management*/
void MainWindow::on_actionOpenVideo_triggered()
{

    QString filename = QFileDialog::getOpenFileName(this,"Open a file","","Videofile(*.*)"); // check goodness file  --> might use VLC embedded in QT (QTVLC)
    on_stop_clicked();

    player -> setSource(QUrl::fromLocalFile(filename));
   // qDebug()<< QUrl::fromLocalFile(filename.left(filename.lastIndexOf("."))).fileName();
    //on_actionOpenLogs_triggered(QUrl::fromLocalFile(filename.left(filename.lastIndexOf("."))).fileName());
    OpenLog(QUrl::fromLocalFile(filename.left(filename.lastIndexOf("."))).fileName());
    ui->scrollTimeLine->setDisabled(false);
    ui->pushButtonZoomIn->setDisabled(false);
    ui->pushButtonZoomOut->setDisabled(false);
    ui->horizontalSliderZoom->setDisabled(false);

}


void MainWindow::OpenLog(QString videoName)
{
    ui->scrollTimeLine->setDisabled(false);

    QFile inputFile("D:\\0_PHD\\Holo-BLSD\\HoloBLSD-DP\\HoloBLSD-DebriefPlayer\\"+videoName+ ".log");  // change path
    QRegularExpression re("^<LogEntry time=\"(?<hh>[0-9]+):(?<mm>[0-9]+):(?<ss>[0-9]+)\\.(?<millis>[0-9]+)\" owner=\"(?<owner>[^\"]*)\" type=\"(?<type>[^\"]*)\" msg=\"(?<msg>[^\"]*)\" />$");
    if (inputFile.open(QIODevice::ReadOnly))
    {
        int i =0;
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          QRegularExpressionMatch match = re.match(line);
          if(match.hasMatch()){
              i++;
              err =0;
              war =0;
              int hh = match.captured("hh").toInt();
              int mm = match.captured("mm").toInt();
              int ss = match.captured("ss").toInt();
              int millis = match.captured("millis").toInt();
              QString owner = match.captured("owner");
              QString type = match.captured("type");
              QString msg = match.captured("msg");

              int totMillis = millis/10000 + 1000*(ss + 60*(mm + 60*(hh)));
              InspectorPopulator(msg);
              AddActivityToTL(totMillis, owner, type,msg,war,err);
          }
       }
       inputFile.close();
    }
    nodes.append(events);
}

void MainWindow::InspectorPopulator(QString _msg){  // creare metodo analogo per ogni ramo di ae
    QRegularExpression exp("(?<log>[a-zA-Z]+): ([a-zA-Z]+( [a-zA-Z]+)+)", QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch match= exp.match(_msg);
    if(match.captured("log") == "ERROR"){
        errorsNum++;
        err++;
        ui->label_int1->setText(QString::number(errorsNum));
    }else if(match.captured("log") == "WARNING"){
        warningsNum++;
        war++;
        ui->label_int2->setText(QString::number(warningsNum++));
    }
}


void MainWindow::AddActivityToTL(int _time, QString _owner, QString _type, QString _msg, int war, int err)
{
    bool found = false;

    foreach (ActivityEntry* ae, nodes) {
        //qDebug() <<"checking " << _owner << " vs " << ae->owner ;
        i++;
        if(ae->owner == _owner){
            if(_type=="Event"){
                int tempnumAct = ae->numAct;
                ActivityEntry* ae = new ActivityEntry{_time,0,_owner,_type, _msg, tempnumAct ,war,err,true};
                nodes.append(ae);
                found = true;
                break;
            }else{
                ae->length = (_time - ae->GetTime());
                //qDebug() << _owner << " is node equal to " << ae->owner ;
                found = true;
                break;
            }
        }
    }
    if(!found){
        actNum++;
       // qDebug()<< actNum;
        ActivityEntry* ae = new ActivityEntry{_time,0,_owner,_type, _msg, actNum,war,err,_type=="Event"};
        nodes.append(ae);
        //qDebug() <<"adding " << ae->owner ;
    }
}

void MainWindow::RepToCSV(QString actDuplicate)
{
   // qDebug()<< actDuplicate;

}

void MainWindow::DrawActivities(){
    foreach (ActivityEntry* ae, nodes) {
         Activity act{ae->GetOwner(),ae->war,ae->err,(float) ae->GetTime(), (float) ae->GetLength(),true,ae->numAct,ae->GetMsg(),ae->isEvent};  // might be cool to put colorcoding
         activityNodes->append(act);
      //  qDebug()<< act.nameAct << " in present: " << ui->listWidgetActivities->findItems(act.nameAct,Qt::MatchContains).isEmpty();

         if(ui->listWidgetActivities->findItems(act.nameAct,Qt::MatchContains).isEmpty()){
             act.actListItemWidget->setToolTip("Event Name : " + act.message);  // todo : deve diventare il msg dell'event
            ui->listWidgetActivities->addItem(act.actListItemWidget);
         }

    }
    UpdateTimeLine(tlScale);
}




/*Video controls*/
void MainWindow::on_stop_clicked()
{
    player->stop();
    qDebug()<< "stopping";
    ui->statusBar ->showMessage("Video stopped");
    //qDebug()<<"this is video length in stop: " <<videoLength;
    UpdateTimeLineLength(videoLength);

}

void MainWindow::on_pause_clicked()
{
    player->pause();
    qDebug()<< "pausing";
    ui->statusBar ->showMessage("Video paused");
    UpdateTimeLineLength(videoLength);
}

void MainWindow::on_play_clicked()
{
    player->play();
    qDebug()<< "playing";
    ui->statusBar ->showMessage("Playing video");
    UpdateTimeLineLength(videoLength);
}

/*controllo cursore*/
void MainWindow::MoveVideoCursor(int moving){
    timeline->UpdateVideoCursorX(moving * tlScale);
}

void MainWindow::SlotVideoCursor(float x){
    emit SignalVideoCursor(x / tlScale);
}






