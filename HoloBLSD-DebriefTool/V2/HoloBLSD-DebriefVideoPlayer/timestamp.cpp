#include "timestamp.h"
#include "qdebug.h"

Timestamp::Timestamp(QObject *parent)
    : QObject{parent}
{

}
Timestamp::Timestamp(int _time, QString _type, QString _msg){

    qDebug()<< "timestamp : creating - "<< QString::number(_time)<< ", " << _type << ", " << _msg ;
    time= _time;
    type=_type;
    msg =_msg;
}
Timestamp::~Timestamp(){
    delete this;
}

int Timestamp::GetTime(){
    return time;
}
