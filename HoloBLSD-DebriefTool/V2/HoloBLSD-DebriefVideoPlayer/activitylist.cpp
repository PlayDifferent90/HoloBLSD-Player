#include "activitylist.h"

ActivityList::ActivityList(QWidget *parent, int _width, int _height)
    : QWidget{parent}
{
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

    //todo: connect(activityList, &QListWidget::itemClicked, parent, &TabWidget::ActivityTextInInspector);
}

void ActivityList::AddActivityItem(QString _text){
        activityList->addItem(_text);

}

QWidget* ActivityList::ActivityWidget(){
    return localWidget;
}

ActivityList::~ActivityList(){
    delete this;
}
