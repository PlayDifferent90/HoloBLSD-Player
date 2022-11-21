#include "uservisibilitybutton.h"


UserVisibilityButton::UserVisibilityButton(FileOpener* _fo, QString _user, QWidget* _parent)
{
    fo=_fo;
    user=_user;
    //todo: cambio colore icone e rimozione nome user
    button= new QPushButton(visibilityIcon, user,this);
    connect(button, &QPushButton::pressed, this, &UserVisibilityButton::NodeVisibilitySwitch);
}

void UserVisibilityButton::NodeVisibilitySwitch(){
    foreach(Activity* act, fo->GetActivities()){
        foreach(Node* n, act->GetNodes()){
            if(n->GetUserID()==user){
               qDebug()<<"user node "<< user <<" vs "<<n->GetUserID();
                n->NodeSwitch();
                this->ChangeIcon(n->IsVisible());
                emit VisibilityPressed();
            }
        }
    }
}

QPushButton* UserVisibilityButton::GetButton(){
    return button;
}

void UserVisibilityButton::ChangeIcon(bool _vis){
    if(_vis){
        button->setIcon(visibilityIcon);
    }else{

        button->setIcon(invisibilityIcon);
    }
}
//todo:cambio icone in sibling
