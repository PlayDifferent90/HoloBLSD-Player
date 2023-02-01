#ifndef FILEOPENER_H
#define FILEOPENER_H

#include "activity.h"
#include "node.h"
#include "qurl.h"
#include "qfile.h"
#include "qregularexpression.h"
#include "qtextstream.h"
#include <QObject>

class FileOpener: public QObject
{
    Q_OBJECT
public:
    FileOpener();

    //FileOpener(QString _fileName);
    FileOpener(QString _userID);
    void OpenLog(QString _fileName);
    int GetErrors();
    int GetWarnings();
    QString GetUser();
    QList<Activity *> GetActivities();
    int GetDuration();
    void OpenLogMaster(QList<QString> _files);
    int GetUserNodeID();
    void SetUsersList(QList<QString> _u);
    QList<QString> GetUsersList();
private:
    QString userID;
    int durationTime =0;
    int errors=0;
    int warnings=0;
    int activityID = 0;
    bool actFound=false;
    QList<Activity*> activities;
    bool DetectErr(QString _msg);
    bool DetectWar(QString _msg);
    void CreateActivity(int _time, QString _owner, QString _type, QString _msg);
    int userNodeID =0;
    QList<QString> usersList;
signals:
    void FileRead();
    void MasterFileRead(int users);

};

#endif // FILEOPENER_H
