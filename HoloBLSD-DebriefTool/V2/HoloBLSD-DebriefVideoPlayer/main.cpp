#include "mainwindow.h"
#include "qdatetime.h"
#include <QApplication>

#include <QDir>
#include <QtGlobal>
#include <stdio.h>
#include <stdlib.h>
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    QString debugMsg ="";
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";

    debugMsg += function;
    debugMsg += "   -   ";
    debugMsg += localMsg.constData();
    QFile outFile(QDir::currentPath() + "\\LogHoloBLSD.txt");
        outFile.open(QIODevice::WriteOnly | QIODevice::Append);
        QTextStream ts(&outFile);
        ts << debugMsg <<  Qt::endl;
}



int main(int argc, char *argv[])
{
    qDebug()<< QDir::currentPath();
 //   qInstallMessageHandler(myMessageOutput);  //comment this line for debugging in QT Creator

    QApplication a(argc, argv);

    QFile style(":/Styles/Combinear.qss");
    style.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(style.readAll());
    a.setStyleSheet(styleSheet);

    MainWindow w;
    w.show();
    return a.exec();
}
