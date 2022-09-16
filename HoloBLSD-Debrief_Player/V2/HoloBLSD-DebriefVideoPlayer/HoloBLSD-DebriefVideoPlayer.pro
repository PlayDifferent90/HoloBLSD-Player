QT       += core gui multimedia multimediawidgets xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    activitylist.cpp \
    fileopener.cpp \
    inspector.cpp \
    main.cpp \
    mainwindow.cpp \
    summary.cpp \
    tabwidget.cpp \
    theme.cpp \
    timeline.cpp \
    timelinecursor.cpp \
    timelinewidget.cpp \
    videoplayer.cpp

HEADERS += \
    activitylist.h \
    fileopener.h \
    inspector.h \
    mainwindow.h \
    summary.h \
    tabwidget.h \
    theme.h \
    timeline.h \
    timelinecursor.h \
    timelinewidget.h \
    videoplayer.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
