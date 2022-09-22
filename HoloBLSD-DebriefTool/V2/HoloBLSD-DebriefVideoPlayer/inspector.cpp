#include "inspector.h"

Inspector::Inspector(QWidget *parent, int _width, int _height)
    : QWidget{parent}
{
    //inspector
    inspectorTabs = new QTabWidget(this);
    inspectorTabs->setMaximumSize(_width,_height);

    inspectorLabel = new QLabel("Inspector");
    inspectorLabel->setMaximumSize(_width,_height/8);


    localLayout = new QVBoxLayout(this);
    localLayout->addWidget(inspectorLabel);
    localLayout->addWidget(inspectorTabs);

    localWidget = new QWidget(this);
    localWidget->setLayout(localLayout);
    localWidget->setMaximumSize(_width,_height);
}

Inspector::~Inspector(){
    delete this;
}

QWidget* Inspector::InspectorWidget(){
    return localWidget;
}

void Inspector::AddUserTab(QString _userName){
    QWidget* userInspectorTab = new  QWidget(this);
    users.append(userInspectorTab);
    inspectorText= new QLabel("this is the Ispector:\n a formattd file will go here");
    inspectorTabs->addTab(userInspectorTab,_userName);
    inspectorLayout = new QGridLayout(userInspectorTab);
    inspectorLayout->addWidget(inspectorText,0,0,1,1);
}
