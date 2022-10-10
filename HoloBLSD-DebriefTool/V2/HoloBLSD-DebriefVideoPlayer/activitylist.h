#ifndef ACTIVITYLIST_H
#define ACTIVITYLIST_H

#include <QObject>
#include <QWidget>
#include "qboxlayout.h"
#include "qlabel.h"
#include "qlistwidget.h"
#include "fileopener.h"
class ActivityList : public QWidget
{
    Q_OBJECT
public:
    explicit ActivityList(QWidget *parent = nullptr);

    void AddActivityItem(QString _text, bool _visib);
    ActivityList(QWidget *parent, int _width, int _height, FileOpener* _fileOpener);
    QWidget *ActivityWidget();
    ~ActivityList();
public slots:
    void AddActivityInList(QString _name,bool _visib);
    void FlushActivities();
private:
    QLabel* activityLabel;
    QListWidget* activityList;
    QBoxLayout* localLayout;
    QWidget* localWidget;
    FileOpener* fileOpener;

    void Selected();
    void Switch();
    void SelectedItem(QListWidgetItem *item);
    void SwitchItem(QListWidgetItem *item);

    const QIcon visible = QIcon(":/Icons/VideoIcon/Visibility_gold.png");
    const QIcon invisible = QIcon(":/Icons/VideoIcon/InvisibilityClosed_gold.png");
signals:
    void DoubleClicked();
    void Clicked(QString name);//, int ID, QList<Node*> nodes,bool visibility);
   // void AddedActivityToList();
};

#endif // ACTIVITYLIST_H
