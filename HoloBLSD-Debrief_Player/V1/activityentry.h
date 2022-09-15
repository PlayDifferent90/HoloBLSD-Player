#ifndef ACTIVITYENTRY_H
#define ACTIVITYENTRY_H

#include <QObject>

class ActivityEntry
{
public:
    ActivityEntry();
    void SetTime(QString _t);
    void SetMsg(QString _m);
    QString GetType();
    QString GetOwner();
    QString GetMsg();
    int GetTime();
    int GetNumAct();
    int err,war =0;
    bool isEvent = false;

   // ActivityEntry(int _time, int duration, QString _owner, QString _type, QString _msg, int _numAct);
    ~ActivityEntry();
    void SetLength(float _length);
    int GetLength();
public:
    int time;
    int numAct;
    float length;
    QString owner;
    QString type;
    QString msg;
    ActivityEntry(int _time, int duration, QString _owner, QString _type, QString _msg, int _numAct, int _war, int _err, bool _isEvent);
};

#endif // ACTIVITYENTRY_H
