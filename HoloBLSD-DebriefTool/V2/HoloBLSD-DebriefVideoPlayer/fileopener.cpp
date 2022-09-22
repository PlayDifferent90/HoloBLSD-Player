#include "fileopener.h"
#include "qdebug.h"

FileOpener::FileOpener(QString _fileName, int _userID)
{
    //one for each file
    userID=_userID;
    OpenLog(_fileName);


}
void FileOpener::OpenLog(QString _fileName)
{
    qDebug()<< "Opening file : " << _fileName;
    QFile inputFile(_fileName);  // change path #URL
    //QFile inputFile("D:\\0_PHD\\Holo-BLSD\\HoloBLSD-DP\\HoloBLSD-DebriefTool\\V2\\Debrief_1\\recipe_test.log");  // change path #URL
    QRegularExpression regEx("^<LogEntry time=\"(?<hh>[0-9]+):(?<mm>[0-9]+):(?<ss>[0-9]+)\\.(?<millis>[0-9]+)\" owner=\"(?<owner>[^\"]*)\" type=\"(?<type>[^\"]*)\" msg=\"(?<msg>[^\"]*)\" />$");
    if (inputFile.open(QIODevice::ReadOnly))
    {
        int i =0;
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          QRegularExpressionMatch match = regEx.match(line);
          if(match.hasMatch()){
              i++;
              errors =0;
              warnings =0;
              int hh = match.captured("hh").toInt();
              int mm = match.captured("mm").toInt();
              int ss = match.captured("ss").toInt();
              int millis = match.captured("millis").toInt();
              QString owner = match.captured("owner");
              QString type = match.captured("type");
              QString msg = match.captured("msg");

              int totMillis = millis/10000 + 1000*(ss + 60*(mm + 60*(hh)));
              CreateActivity(totMillis, owner, type,msg,warnings,errors);
          }
       }
       inputFile.close();

    }
}

bool FileOpener::DetectErr(QString _msg){
    QRegularExpression exp("(?<log>[a-zA-Z]+): ([a-zA-Z]+( [a-zA-Z]+)+)", QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch match= exp.match(_msg);
    if(match.captured("log") == "ERROR"){
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

void FileOpener::CreateActivity(int _time, QString _owner, QString _type, QString _msg, int war, int err)
{

    foreach (Activity* act, activities) {
        if(act->GetName() == _owner){
            if(_type=="Event"){
                Timestamp* timestampEvent = new Timestamp{_time, _type, _msg};
                QList<Node*> nodes = act->GetNodesByUser(userID);
                if (!nodes.empty()){
                    foreach (Node* n, nodes) {
                        if(n->GetFinish()==NULL){
                            n->AddEvent(timestampEvent, DetectErr(_msg),DetectWar(_msg));
                        }
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
                        if(n->GetFinish()==NULL){
                            n->SetFinish(timestampEvent);
                        }
                    }
                }else{
                    qDebug()<< "ERROR: node " << _owner << "finishes without starting";
                }
                actFound =true;
                return;
            }else if((_type=="NodeTriggered" )){  // todo: check and finish
                Timestamp* timestampTriggered = new Timestamp{_time, _type, _msg};
                Node* node = new Node{timestampTriggered,userID};
                act->AddNode(node);
                actFound =true;
                return;
            }
        }
        actFound = false;
    }
    if((_type=="NodeTriggered" && !actFound)){  // todo: check and finish
        activityID++;
        Activity* activity = new Activity{_owner, activityID};
        Timestamp* timestampTriggered = new Timestamp{_time, _type, _msg};
        Node* node = new Node{timestampTriggered,userID};
        activity->AddNode(node);
        activities.append(activity);
        return;
    }

}

QList<Activity*> FileOpener::GetAtivities(){
    return activities;
}
