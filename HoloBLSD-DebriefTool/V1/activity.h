#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QListWidget>
#include <QObject>
#include <QWidget>

class Activity
{

public:
    QListWidgetItem* actListItemWidget;
    QPointF* actStartingPoint;
    QRect* actRect;
    int actLength;
    bool isVisible;
    int actID;
    int rectHeight = 30;
    int startTime;
    int alignement = 18;
    float zoomScale = 1;
    bool isEvent = false;
    QString nameAct;
    QString message;
    QIcon visibleIcon = QIcon(":/Visibility_gold.png");
    QIcon invisibleIcon = QIcon(":/Invisibility_lightgrey.png");

    void visibilitySwitch();
    QListWidgetItem *ActListItem();
    void UpdateRectHeight(bool show);
    ~Activity();
    QPointF UpdateStartingPoint(int lineNumber, float scale);
    void UpdateRectLength(float scale);
    void UpdateSP(float scale);
    void Zoom(float scale);
    void SetIcon(bool visibility);
    Activity(QString name, int err, int war, float start, float length, bool visibility, int numberID, QString message, bool _isEvent);
};

#endif // ACTIVITY_H
