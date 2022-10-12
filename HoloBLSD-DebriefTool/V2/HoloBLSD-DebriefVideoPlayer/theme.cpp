#include "theme.h"
#include "qdebug.h"

Theme::Theme()
{
}

QBrush Theme::RandomUserColor(QString _user)
{
    float userRand=0;
    for(const auto character: _user){
        userRand += character.unicode();
    }
    userRand = (float)userRand/(1000.0f);
    qDebug()<<"unicode "<< userRand;
    QColor userRandom{(int)((float)48/userRand) , (int)((float)196/userRand), (int)((float)214/userRand)};  //29,98,107
    QBrush userBrush{userRandom};
    return userBrush;
}
