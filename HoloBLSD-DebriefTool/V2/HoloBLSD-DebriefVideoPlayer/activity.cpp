#include "activity.h"
#include "qapplication.h"
#include "qdebug.h"

Activity::Activity(QObject *parent)
    : QObject{parent}
{

}

Activity::Activity(QString _name, int _actID){

    actName=_name;
    actID=_actID;
}
Activity::~Activity(){
    delete this;
}


void Activity::AddNode(Node* _node) {
    nodes.append(_node);
}

int Activity::GetActID(){
    return actID;
}

QList<Node*> Activity::GetNodes(){
    return nodes;
}

void Activity::ActivitySwitch(){
    isVisibile=!isVisibile;
}

QList<Node*> Activity::GetNodesByUser(QString _user){
    QList<Node*> usersNodes;
    foreach (Node* n, nodes){
        if(n->GetUserID()==_user){
            usersNodes.append(n);
        }
    }
    return usersNodes;
}

QList<Node*> Activity::GetVisibleNodes(){
    QList<Node*> visibleNodes;
    foreach (Node* n, nodes){
        if(n->IsVisible()){
            visibleNodes.append(n);
        }
    }
    return visibleNodes;
}

QString Activity::GetName(){
    return actName;
}

int Activity::GetUsersNumber(bool _getAll){
    QList<QString> countingUsers;
    foreach(Node* n, nodes){
        if(!countingUsers.contains(n->GetUserID()) && (n->IsVisible() || _getAll)){
            countingUsers.append(n->GetUserID());
        }
    }
   qDebug()<<" users per activity " <<this <<countingUsers.count();
    return countingUsers.count();
}

bool Activity::GetVisibility(){
    return isVisibile;
}
