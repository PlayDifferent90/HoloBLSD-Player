#include "theme.h"
#include "qdebug.h"

Theme::Theme()
{

}

QBrush Theme::RandomUserColor(QString _user)
{
    int userRand =  _user.length();
   // qDebug()<<"_userRand value"<< userRand;
    QColor userRandom{(255)/userRand , (255)/_user.length(), 255};
    QBrush userBrush{userRandom};
    return userBrush;
}
