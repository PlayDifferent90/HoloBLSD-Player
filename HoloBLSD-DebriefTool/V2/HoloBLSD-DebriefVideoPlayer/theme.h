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

    qreal outlineSize = 0;

    QColor cursorPenColor = QColor(183,134,32);
    QColor cursorBrushColor = QColor(183,134,32);


    QColor bluedimmed{45,114,178};
    QColor blue{57,92,107};
    QColor skyblue{74,123,157};
    QColor lightblue{118,152,179};
    QColor greyBlue{78,128,152};
    QColor lightgreen{166,211,160};
    QColor red{219,84,97};
    QColor orange{255,127,00};
    QColor yellow{243,255,185};
    QColor verticalLineColor{70,70,70};

    QPen penBlue {blue,outlineSize};
    QPen penBlack {Qt::black,outlineSize};
    QPen penLineTimeStop{verticalLineColor,1};

    QBrush nodeBrush {orange};
    QBrush eventBrush {red};

};

#endif // THEME_H
