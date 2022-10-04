#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QObject>
#include "node.h"

class Activity : public QObject
{
    Q_OBJECT
public:
    explicit Activity(QObject *parent = nullptr);
    Activity(QString _nome, int _actID);
    ~Activity();
    void AddNode(Node *_node);
    int GetActID();
    QList<Node*> GetNodes();
    void ActivitySwitch();
    QString GetName();
    QList<Node *> GetNodesByUser(QString _user);
    int GetUsersNumber();
    bool GetVisibility();
private:
    QString actName;
    QList<Node*> nodes;
    int actID;
    bool isVisibile = true;

signals:

};

#endif // ACTIVITY_H
