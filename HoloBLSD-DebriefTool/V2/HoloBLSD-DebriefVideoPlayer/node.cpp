#include "node.h"
#include "qdebug.h"

Node::Node(QObject *parent)
    : QObject{parent}
{

}
Node::Node(Timestamp* _tStart, QString _userID){
    tStart = _tStart;
    tFinish = _tStart;
    userID =_userID;
}

Node::~Node(){
    delete this;
}

QString Node::GetUserID(){
    return userID;
}

void Node::AddEvent(Timestamp* _tEvent, bool _isError, bool _isWarning){
    tEvents.append(_tEvent);

    if(_isError){
        errors++;//chenge color
    }
    else if(_isWarning){
        warnings++; //chenge color
    }

    if(tFinish!=NULL){
        qDebug()<<"Error detected : Event at time " << _tEvent->GetTime() << " is happening after Node Finished";
    }
}
void Node::SetFinish(Timestamp* _tFinish){
    tFinish=_tFinish;

}
void Node::NodeSwitch(){
    isVisible = !isVisible;
}

Timestamp* Node::GetStart(){
    return tStart;
}

Timestamp* Node::GetFinish(){
    return tFinish;
}

QList<Timestamp*> Node::GetEvents(){
    return tEvents;
}

int Node::GetErr(){
    return  errors;
}
int Node::GetWar(){
    return  warnings;
}

bool Node::IsVisible(){
    return isVisible;
}
