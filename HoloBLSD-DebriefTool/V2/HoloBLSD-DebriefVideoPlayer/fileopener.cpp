#include "fileopener.h"
#include "qapplication.h"
#include "qdebug.h"
#include "qfileinfo.h"

FileOpener::FileOpener(QString _userID)
{
    userID=_userID;
}
void FileOpener::OpenLog(QString _fileName)
{

    // todo: add control on video presence

    QApplication::setOverrideCursor(Qt::WaitCursor);
   qDebug()<< "Opening file : " << _fileName;
    QFile inputFile(_fileName);  // change path #URL
    QRegularExpression regEx("^<LogEntry time=\"(?<hh>[0-9]+):(?<mm>[0-9]+):(?<ss>[0-9]+)\\.(?<millis>[0-9]+)\" owner=\"(?<owner>[^\"]*)\" type=\"(?<type>[^\"]*)\" msg=\"(?<msg>[^\"]*)\" />$");
    if (inputFile.open(QIODevice::ReadOnly))
    {
        int i =0;
       QTextStream in(&inputFile);

     //  qDebug()<<"reading file ...";
       while (!in.atEnd())
       {
       //  qDebug()<<"Reading line ";
          QString line = in.readLine();
          QRegularExpressionMatch match = regEx.match(line);
          if(match.hasMatch()){
          //   qDebug()<<"Matcha t line "<<i;
              i++;
              int hh = match.captured("hh").toInt();
              int mm = match.captured("mm").toInt();
              int ss = match.captured("ss").toInt();
              int millis = match.captured("millis").toInt();
              QString owner = match.captured("owner");
              QString type = match.captured("type");
              QString msg = match.captured("msg");

              int totMillis = millis/10000 + 1000*(ss + 60*(mm + 60*(hh)));
              if(owner== "ACLSTrainingManager"){
                  SummaryScenario(msg);
              }else if(msg=="Video Recording Start" && owner == "VideoManager"){
                  SyncTimeline(totMillis);
              }else{
                  CreateActivity(totMillis, owner, type,msg);//,warnings,errors);
              }

          }
       }
       inputFile.close();

       emit FileRead();

       QApplication::restoreOverrideCursor();
    }
}

void FileOpener::OpenLogMaster(QList<QString> _files)
{
    QApplication::setOverrideCursor(Qt::WaitCursor);

    QString userSwap = userID;
    userNodeID =1;
    foreach (QString f, _files) {
        QFileInfo fileInfo(f);
        userID = fileInfo.baseName();
        OpenLog(f);
        userNodeID++;
    }
    userID=userSwap;
    emit MasterFileRead(_files.length());

    QApplication::restoreOverrideCursor();
}

bool FileOpener::DetectErr(QString _msg){
    QRegularExpression exp("(?<log>[a-zA-Z]+): ([a-zA-Z]+( [a-zA-Z]+)+)", QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch match= exp.match(_msg);
    if(match.captured("log") == "ERROR"){
        qDebug()<<"     Error found ";
        errors++;
        return true;
    }
    return false;
}
bool FileOpener::DetectWar(QString _msg){
    QRegularExpression exp("(?<log>[a-zA-Z]+): ([a-zA-Z]+( [a-zA-Z]+)+)", QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch match= exp.match(_msg);
    if(match.captured("log") == "WARNING"){
        warnings++;
        return true;
    }
    return false;
}

void FileOpener::SummaryScenario(QString _msg){
    summary.append(_msg);
}

void FileOpener::SyncTimeline(int _totMillis){
    ciackTime = _totMillis;
}

void FileOpener::CreateActivity(int _time, QString _owner, QString _type, QString _msg)//, int war, int err)
{

   qDebug()<< "time = " << _time << "own "<< _owner << "Type "<< _type;
    foreach (Activity* act, activities) {
        if(act->GetName() == _owner){
            if(_type=="Event"){
                Timestamp* timestampEvent = new Timestamp{_time, _type, _msg};
                QList<Node*> nodes = act->GetNodesByUser(userID);
                if (!nodes.empty()){
                    foreach (Node* n, nodes) {
                      //  if(n->GetFinish()==n->GetStart()){
                            n->AddEvent(timestampEvent, DetectErr(_msg),DetectWar(_msg));
                     //   }
                    }
                }else{
                    qDebug()<< "ERROR: node " << _owner << "has event before being triggered";
                }
                actFound =true;
                return;
            }else if (_type=="NodeCompleted"){
                Timestamp* timestampEvent = new Timestamp{_time, _type, _msg};
                QList<Node*> nodes = act->GetNodesByUser(userID);
                if (!nodes.empty()){
                    foreach (Node* n, nodes) {
                      //  if(n->GetFinish()==n->GetStart()){
                            n->SetFinish(timestampEvent);
                            if(n->GetFinish()->GetTime()>durationTime)
                                durationTime=n->GetFinish()->GetTime();
                                qDebug()<<"duration" << durationTime;
                     //   }
                    }
                }else{
                    qDebug()<< "ERROR: node " << _owner << "finishes without starting";
                }
                actFound =true;
                return;
            }else if((_type=="NodeTriggered" )){
                Timestamp* timestampTriggered = new Timestamp{_time, _type, _msg};
               qDebug()<< "creating user ID: " << userID;
                Node* node = new Node{timestampTriggered,userID};
                act->AddNode(node);
                actFound =true;
                return;
            }
        }
        actFound = false;
    }
    if((_type=="NodeTriggered" && !actFound)){
        activityID++;
        Activity* activity = new Activity{_owner, (int)activityID};
        Timestamp* timestampTriggered = new Timestamp{_time, _type, _msg};
        Node* node = new Node{timestampTriggered,userID};
        activity->AddNode(node);
        activities.append(activity);
        return;
    }

}

QList<Activity*> FileOpener::GetActivities(){
    return activities;
}

int FileOpener::GetDuration(){
    return durationTime;
}

int FileOpener::GetErrors(){
    return errors;
}

int FileOpener::GetWarnings(){
    return warnings;
}

QString FileOpener::GetUser(){
    return userID;
}

QList<QString> FileOpener::GetSummary(){
    return summary;
}

void FileOpener::SetUsersList(QList<QString> _u){
    usersList=_u;
}
QList<QString> FileOpener::GetUsersList(){
    return usersList;
}
