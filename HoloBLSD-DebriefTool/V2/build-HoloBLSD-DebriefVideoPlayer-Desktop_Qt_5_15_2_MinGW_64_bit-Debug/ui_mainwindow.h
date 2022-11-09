/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpenSingleUserFile;
    QAction *actionOpen_File;
    QAction *actionOpen_Session;
    QAction *actionSave_Session;
    QAction *actionPlay;
    QAction *actionPause;
    QAction *actionStop;
    QAction *actionVolume_Down;
    QAction *actionVolume_Up;
    QAction *actionVolume_Mute;
    QAction *actionZoomIn;
    QAction *actionZoomOut;
    QAction *actionNew_Session;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QMenuBar *menubar;
    QMenu *Files;
    QMenu *menuVideo;
    QMenu *menuTimeline;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1224, 722);
        actionOpenSingleUserFile = new QAction(MainWindow);
        actionOpenSingleUserFile->setObjectName(QString::fromUtf8("actionOpenSingleUserFile"));
        actionOpen_File = new QAction(MainWindow);
        actionOpen_File->setObjectName(QString::fromUtf8("actionOpen_File"));
        actionOpen_Session = new QAction(MainWindow);
        actionOpen_Session->setObjectName(QString::fromUtf8("actionOpen_Session"));
        actionSave_Session = new QAction(MainWindow);
        actionSave_Session->setObjectName(QString::fromUtf8("actionSave_Session"));
        actionPlay = new QAction(MainWindow);
        actionPlay->setObjectName(QString::fromUtf8("actionPlay"));
        actionPause = new QAction(MainWindow);
        actionPause->setObjectName(QString::fromUtf8("actionPause"));
        actionStop = new QAction(MainWindow);
        actionStop->setObjectName(QString::fromUtf8("actionStop"));
        actionVolume_Down = new QAction(MainWindow);
        actionVolume_Down->setObjectName(QString::fromUtf8("actionVolume_Down"));
        actionVolume_Up = new QAction(MainWindow);
        actionVolume_Up->setObjectName(QString::fromUtf8("actionVolume_Up"));
        actionVolume_Mute = new QAction(MainWindow);
        actionVolume_Mute->setObjectName(QString::fromUtf8("actionVolume_Mute"));
        actionZoomIn = new QAction(MainWindow);
        actionZoomIn->setObjectName(QString::fromUtf8("actionZoomIn"));
        actionZoomOut = new QAction(MainWindow);
        actionZoomOut->setObjectName(QString::fromUtf8("actionZoomOut"));
        actionNew_Session = new QAction(MainWindow);
        actionNew_Session->setObjectName(QString::fromUtf8("actionNew_Session"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1224, 21));
        Files = new QMenu(menubar);
        Files->setObjectName(QString::fromUtf8("Files"));
        menuVideo = new QMenu(menubar);
        menuVideo->setObjectName(QString::fromUtf8("menuVideo"));
        menuTimeline = new QMenu(menubar);
        menuTimeline->setObjectName(QString::fromUtf8("menuTimeline"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(Files->menuAction());
        menubar->addAction(menuVideo->menuAction());
        menubar->addAction(menuTimeline->menuAction());
        Files->addAction(actionOpen_File);
        Files->addSeparator();
        Files->addAction(actionOpen_Session);
        Files->addAction(actionSave_Session);
        Files->addAction(actionNew_Session);
        menuVideo->addAction(actionPlay);
        menuVideo->addAction(actionPause);
        menuVideo->addAction(actionStop);
        menuVideo->addSeparator();
        menuVideo->addAction(actionVolume_Down);
        menuVideo->addAction(actionVolume_Up);
        menuVideo->addAction(actionVolume_Mute);
        menuTimeline->addAction(actionZoomIn);
        menuTimeline->addAction(actionZoomOut);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpenSingleUserFile->setText(QCoreApplication::translate("MainWindow", "Open File", nullptr));
        actionOpen_File->setText(QCoreApplication::translate("MainWindow", "Open File", nullptr));
        actionOpen_Session->setText(QCoreApplication::translate("MainWindow", "Open Session", nullptr));
        actionSave_Session->setText(QCoreApplication::translate("MainWindow", "Save Session", nullptr));
        actionPlay->setText(QCoreApplication::translate("MainWindow", "Play", nullptr));
        actionPause->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
        actionStop->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        actionVolume_Down->setText(QCoreApplication::translate("MainWindow", "Volume Down", nullptr));
        actionVolume_Up->setText(QCoreApplication::translate("MainWindow", "Volume Up", nullptr));
        actionVolume_Mute->setText(QCoreApplication::translate("MainWindow", "Volume Mute", nullptr));
        actionZoomIn->setText(QCoreApplication::translate("MainWindow", "ZoomIn", nullptr));
        actionZoomOut->setText(QCoreApplication::translate("MainWindow", "ZoomOut", nullptr));
        actionNew_Session->setText(QCoreApplication::translate("MainWindow", "New Session", nullptr));
        Files->setTitle(QCoreApplication::translate("MainWindow", "Files", nullptr));
        menuVideo->setTitle(QCoreApplication::translate("MainWindow", "Video", nullptr));
        menuTimeline->setTitle(QCoreApplication::translate("MainWindow", "Timeline", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
