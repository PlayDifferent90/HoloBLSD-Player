#include "activity.h"

//suggested in https://stackoverflow.com/questions/73490057/how-to-create-an-object-in-c-qt?noredirect=1#comment129788937_73490057
/*Activity::Activity(QString name, int err, int war,int startTime,int length, bool isVisible,int numberID)
    : actIsVisible(isVisible), actID(numberID)
{
}*/

Activity::Activity(QString name, int err, int war,float start,float length, bool visibility,int numberID,QString _message, bool _isEvent)

{
    nameAct=name;
    actLength = length;
    startTime = start;
    isVisible = visibility;
    actID = numberID;
    message=_message;
    actListItemWidget = new QListWidgetItem();
    actListItemWidget->setText(name + " (Err:" + QString::number(err) + ";War:" + QString::number(war)+")");

    actStartingPoint = new QPointF( startTime,(actID  * rectHeight) + alignement );

    actRect = new QRect (0,0,actLength,rectHeight);
    isEvent = _isEvent;

    SetIcon(isVisible);

}

void Activity::visibilitySwitch(){
    isVisible = !isVisible;
    SetIcon(isVisible);
}

//todo: move in timeline
QPointF Activity::UpdateStartingPoint(int lineNumber, float scale){
    //rememeber to update this for zoom
    actStartingPoint = new QPointF( startTime*scale,(lineNumber -1) * rectHeight +alignement );
    return *actStartingPoint;
}



void Activity::UpdateRectHeight(bool show){
    actRect = new QRect (0,0,actLength,rectHeight*show);
}

void Activity::UpdateRectLength(float scale){
    actRect = new QRect (0,0,actLength*scale,rectHeight);
}

void Activity::Zoom(float scale){
    UpdateRectLength(scale);
}

void Activity::SetIcon(bool visibility){
    if(visibility){
        this->actListItemWidget->setIcon(visibleIcon);
    }else{
        this->actListItemWidget->setIcon(invisibleIcon);
    }
}


Activity::~Activity()
{
}
