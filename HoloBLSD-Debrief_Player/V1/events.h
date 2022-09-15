#ifndef EVENTS_H
#define EVENTS_H


#include <QListWidget>
#include <QObject>
#include <QWidget>

class Events
{
public:
    QString name,message;
    float startTime;
    int numberID;
    bool visibility;


    Events();
    Events(QString _name, float _startTime, bool _visibility, int _numberID, QString _message);
};

#endif // EVENTS_H
