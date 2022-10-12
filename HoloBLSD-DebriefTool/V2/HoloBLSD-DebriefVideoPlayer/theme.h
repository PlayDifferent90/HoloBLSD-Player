#ifndef THEME_H
#define THEME_H

#include <QObject>
#include "qcolor.h"
#include "QPen.h"
#include "QBrush.h"

class Theme: public QObject
{
    Q_OBJECT
public:
    Theme();

    //combinear color
    QColor blackA{0,0,0,100};
    QColor darkgrey{46,46,46};
    QColor grey{58,58,58};
    QColor lightGrey{70,70,70};
    QColor yellow{183,134,32};
    QColor whiteA{255,255,255,100};

    //pens
    QPen timelineNodeBorders {blackA,1};
    QPen penLineTimeStop{lightGrey,1};

    //brushes
    QBrush eventBrush {whiteA};  //set alpha
    QBrush TimelineBG{darkgrey};
    QBrush TimelineBGRow{grey};
    QBrush videoCursorBrush{yellow};

    QBrush RandomUserColor(QString _user);
};

#endif // THEME_H
