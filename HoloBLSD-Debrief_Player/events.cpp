#include "events.h"

Events::Events(QString _name, float _startTime, bool _visibility, int _numberID, QString _message)
{

name=_name;
message=_message;
startTime=_startTime;
numberID=_numberID;
visibility=_visibility;
}
