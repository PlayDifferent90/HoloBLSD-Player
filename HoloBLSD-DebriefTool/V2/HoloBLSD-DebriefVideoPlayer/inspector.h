#ifndef INSPECTOR_H
#define INSPECTOR_H

#include "qgridlayout.h"
#include "qlabel.h"
#include "qtabwidget.h"
#include <QObject>
#include <QWidget>

class Inspector : public QWidget
{
    Q_OBJECT
public:
    explicit Inspector(QWidget *parent = nullptr);

    Inspector(QWidget *parent, int _width, int _height);
    QWidget *InspectorWidget();
    ~Inspector();
    void AddUserTab(QString _userName);
private:
     QLabel* inspectorText;
     QTabWidget* inspectorTabs;
     QGridLayout* inspectorLayout;
     //QWidget* userInspectorTab;
     QBoxLayout* localLayout;
     QWidget* localWidget;
     QLabel* inspectorLabel;
     QList<QWidget*> users;


signals:

};

#endif // INSPECTOR_H
