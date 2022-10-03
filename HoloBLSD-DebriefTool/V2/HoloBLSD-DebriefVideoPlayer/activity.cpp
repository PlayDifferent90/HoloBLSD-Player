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

QList<Node*> Activity::GetNodesByUser(int _user){
    QList<Node*> usersNodes;
    foreach (Node* n, nodes){
        if(n->GetUserID()==_user){
            usersNodes.append(n);
        }
    }
    return usersNodes;
}

QString Activity::GetName(){
    return actName;
}

int Activity::GetUsersNumber(){
    QList<int> countingUsers;
    foreach(Node* n, nodes){
        if(!countingUsers.contains(n->GetUserID())){
            countingUsers.append(n->GetUserID());
        }
    }
    return countingUsers.count();
}
