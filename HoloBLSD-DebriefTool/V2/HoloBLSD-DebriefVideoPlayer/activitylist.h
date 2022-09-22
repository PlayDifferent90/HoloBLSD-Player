#ifndef ACTIVITYLIST_H
#define ACTIVITYLIST_H

#include <QObject>
#include <QWidget>
#include "qboxlayout.h"
#include "qlabel.h"
#include "qlistwidget.h"

class ActivityList : public QWidget
{
    Q_OBJECT
public:
    explicit ActivityList(QWidget *parent = nullptr);

    void AddActivityItem(QString _text);
    ActivityList(QWidget *parent, int _width, int _height);
    QWidget *ActivityWidget();
    ~ActivityList();
private:
    QLabel* activityLabel;
    QListWidget* activityList;
    QBoxLayout* localLayout;
    QWidget* localWidget;

signals:

};

#endif // ACTIVITYLIST_H
