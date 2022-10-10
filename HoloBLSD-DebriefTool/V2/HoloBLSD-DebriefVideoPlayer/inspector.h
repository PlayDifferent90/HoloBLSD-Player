#ifndef INSPECTOR_H
#define INSPECTOR_H

#include "qgridlayout.h"
#include "qlabel.h"
#include "qtabwidget.h"
#include "QDateTime"
#include "node.h"
#include "fileopener.h"
#include "qdebug.h"
#include "qscrollarea.h"
#include <QObject>
#include <QWidget>

class Inspector : public QWidget
{
    Q_OBJECT
public:
    explicit Inspector(QWidget *parent = nullptr);

    Inspector(QWidget *parent, int _width, int _height, FileOpener *_fileOpener);
    QWidget *InspectorWidget();
    ~Inspector();
    void SelectActivityText(int _selected = -1);
    void SelectText(QString _actListText);
    void PopulateInspector();
    QWidget *GetInspectorLayout();
    void PopulateMasterInspector();
private:
    QWidget* userInspectorTab;
     QTabWidget* inspectorTabs;
     QGridLayout* inspectorLayout;
     QBoxLayout* localLayout;
     QWidget* localWidget;
     QLabel* inspectorLabel;
     QList<QWidget*> users;
     FileOpener* fo;


     void CurrentTabUpdate(int _i);
signals:

};

#endif // INSPECTOR_H
