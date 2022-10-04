#ifndef NODE_H
#define NODE_H

#include <QObject>
#include "timestamp.h"


class Node : public QObject
{
    Q_OBJECT
public:
    explicit Node(QObject *parent = nullptr);
    Node(Timestamp* _tStart, QString _userID);
    ~Node();
    QString GetUserID();
    void AddEvent(Timestamp* _tEvent, bool _isError, bool _isWarning);
    void SetFinish(Timestamp* _tFinish);
    void NodeSwitch();
    Timestamp *GetStart();
    Timestamp *GetFinish();
    QList<Timestamp *> GetEvents();
private:
    Timestamp* tStart;
    Timestamp* tFinish=NULL;
    QList<Timestamp*> tEvents;
    int errors, warning = 0;
    bool isVisible = true;
    QString userID = "Empty"; // todo: deve essere assegnato e incrementato da chi apre file per

signals:

};

#endif // NODE_H
