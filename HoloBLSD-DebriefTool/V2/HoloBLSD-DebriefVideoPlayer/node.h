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
    int GetErr();
    int GetWar();
    bool IsVisible();
private:
    Timestamp* tStart;
    Timestamp* tFinish=NULL;
    QList<Timestamp*> tEvents;
    int errors=0;
    int warnings = 0;
    bool isVisible = true;
    QString userID = "Empty";

signals:

};

#endif // NODE_H
