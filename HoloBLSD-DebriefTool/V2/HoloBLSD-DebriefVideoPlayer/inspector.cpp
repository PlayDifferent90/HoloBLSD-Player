#include "inspector.h"
#include "qdebug.h"

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
    inspectorText= new QLabel( _userName + " infos will be displayed here;");
    inspectorTabs->addTab(userInspectorTab,_userName);
    inspectorLayout = new QGridLayout(userInspectorTab);
    inspectorLayout->addWidget(inspectorText,0,0,0,0); //todo: move upper
}

void Inspector::UpdateInspector(QString _name, int _ID, QList<Node*> _nodes,bool _visibility){

    QList<QString> _users;
    int _numUsers  =0;
    QString visibility;

    foreach (Node* n, _nodes) {
        if( !_users.contains(n->GetUserID())){
            _users.append(n->GetUserID());
        }
    }

    if(_visibility) visibility= "true";
    else visibility = "false";
    _numUsers = _users.count();
    inspectorText->clear();
    inspectorText->setText("Activity: " + _name + "\n"+"ID : "+ QString::number(_ID) +  "\n" +
                           "Is visible in timeline : " +  visibility + "\n"+
                           "\n" +
                           "this activity has been performed by " + QString::number(_numUsers) +" users  : \n \n" );

    foreach (QString  u, _users){
        inspectorText->setText(inspectorText->text() +
                               "User "  +  u + ":\n" );
        foreach (Node* nn, _nodes) {
            if(nn->GetUserID()==u){
                inspectorText->setText(inspectorText->text() +
                                       "Activity started at: " + QDateTime::fromMSecsSinceEpoch(nn->GetStart()->GetTime()).toString("mm:ss")+" , finished at: " + QDateTime::fromMSecsSinceEpoch(nn->GetFinish()->GetTime()).toString("mm:ss") +"\n" );
            }
        }
    }

}
