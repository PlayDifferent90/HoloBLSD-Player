#ifndef USERVISIBILITYBUTTON_H
#define USERVISIBILITYBUTTON_H

#include "fileopener.h"
#include "qpushbutton.h"
#include "qboxlayout.h"
#include "qdebug.h"
#include <QObject>
#include <QWidget>

class UserVisibilityButton :  public QWidget
{
    Q_OBJECT
public:
    explicit UserVisibilityButton(FileOpener* _fo, QString _user, QObject *parent = nullptr);
    UserVisibilityButton(FileOpener *_fo, QString _user, QWidget *parent);
    QPushButton* GetButton();
private:
    QPushButton* button;
    FileOpener* fo;
    QString user;
    const QIcon visibilityIcon = QIcon(":/Icons/VideoIcon/Invisibility_lightgrey.png");
    const QIcon invisibilityIcon = QIcon(":/Icons/VideoIcon/EyeClosed_white.png");
    void NodeVisibilitySwitch();
    void ChangeIcon(bool _vis);
signals:
    void VisibilityPressed();

};

#endif // USERVISIBILITYBUTTON_H
