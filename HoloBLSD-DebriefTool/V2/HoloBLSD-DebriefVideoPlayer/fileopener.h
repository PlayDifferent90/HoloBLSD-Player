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

    FileOpener(QString _fileName);
    FileOpener(QString _fileName, int _userID);
    QList<Activity *> GetAtivities();
    void OpenLog(QString _fileName);
private:
    int userID;
    int durationTime;
    int errors=0;
    int warnings=0;
    int activityID;
    bool actFound=false;
    QList<Activity*> activities;

    void OpenLog(QUrl videoName);
    void CreateActivity(int _time, QString _owner, QString _type, QString _msg, int war, int err);
    bool DetectErr(QString _msg);
    bool DetectWar(QString _msg);

};

#endif // FILEOPENER_H
