
#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile style("D:\\0_PHD\\Holo-BLSD\\QT\\Timeline-master\\Combinear.qss");
    style.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(style.readAll());
    a.setStyleSheet(styleSheet);

    MainWindow w;
    w.show();

    return a.exec();
}
