#include "activityentry.h"
#include "qdebug.h"

ActivityEntry::ActivityEntry(int _time, int duration, QString _owner, QString _type, QString _msg, int _numAct, int _war, int _err, bool _isEvent)
{
    time =_time;
    owner=_owner;
    type =_type;
    msg  =_msg;
    numAct = _numAct;
    war =_war;
    err =_err;
    isEvent = _isEvent;
}


QString ActivityEntry::GetType(){
    return type;
}

QString ActivityEntry::GetOwner(){
    return owner;
}


int ActivityEntry::GetTime(){
    return time;
}

int ActivityEntry::GetNumAct(){
    return time;
}

QString ActivityEntry::GetMsg(){
    return msg;
}

ActivityEntry::~ActivityEntry(){

}

void ActivityEntry::SetLength(float _length){
    length=_length;
}

int ActivityEntry::GetLength(){
    return time;
}
