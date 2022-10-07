#include "activitylist.h"
#include "qdebug.h"

ActivityList::ActivityList(QWidget *parent, int _width, int _height, FileOpener* _fileOpener)
    : QWidget{parent}
{
    fileOpener =_fileOpener;
    //activityList
    activityLabel = new QLabel("Activities");
    activityLabel->setMaximumSize(_width,_height/(8));

    activityList = new QListWidget(this);
    activityList ->setMaximumSize(_width,_height/(8)*3*7);

    localLayout = new QVBoxLayout(this);
    localLayout->addWidget(activityLabel);
    localLayout->addWidget(activityList);

    localWidget = new QWidget(this);
    localWidget->setLayout(localLayout);
    localWidget->setMaximumSize(_width,_height*3);

    connect(activityList, &QListWidget::itemClicked, this, &ActivityList::SelectedItem);
    connect(activityList, &QListWidget::itemDoubleClicked, this, &ActivityList::SwitchItem);
    //todo: connect(activityList, &QListWidget::itemClicked, parent, &TabWidget::ActivityTextInInspector);
}

void ActivityList::AddActivityItem(QString _text, bool _visib){
    QIcon icon;
    if(_visib){
        icon = visible;
        //qDebug()<< "setting visible icon" << _text;
    }else{
        icon = invisible;
        //qDebug()<< "setting invisible icon" << _text;
    }
   QListWidgetItem* _itm = new QListWidgetItem(icon, _text);
   activityList->addItem(_itm);



}

QWidget* ActivityList::ActivityWidget(){
    return localWidget;
}

ActivityList::~ActivityList(){
    delete this;
}

void ActivityList::AddActivityInList(QString _name,bool _visib){

    this->AddActivityItem(_name,_visib);
   // foreach(Activity*  act , fileOpener->GetActivities()){
   //     if(act->GetName()==_name){
   //         emit AddedActivityToList(act->GetName(),act->GetActID(),act->GetNodes(),act->GetVisibility());
   //     }
   // }
}

void ActivityList::FlushActivities(){
    activityList->clear();
}

void ActivityList::Selected(){
    qDebug()<<"selected "<< this;
}
void ActivityList::Switch(){

}

void ActivityList::SelectedItem(QListWidgetItem *item){
    foreach(Activity*  act , fileOpener->GetActivities()){
        if(act->GetName()==item->text()){
            emit Clicked(act->GetName(),act->GetActID(),act->GetNodes(),act->GetVisibility());
            // todo: set timeline highlighted
        }
    }
}
void ActivityList::SwitchItem(QListWidgetItem *item){
    foreach(Activity*  act , fileOpener->GetActivities()){
        if(act->GetName()==item->text()){
            act->ActivitySwitch();
            emit Clicked(act->GetName(),act->GetActID(),act->GetNodes(),act->GetVisibility());

        }
    }


    emit DoubleClicked();
}
