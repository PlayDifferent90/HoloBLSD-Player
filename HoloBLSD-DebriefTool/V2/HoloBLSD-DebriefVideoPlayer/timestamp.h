#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <QObject>

class Timestamp : public QObject
{
    Q_OBJECT
public:
    explicit Timestamp(QObject *parent = nullptr);
    Timestamp(int _time, QString _type, QString _msg);
    ~Timestamp();
    int GetTime();
private:
    int time  = 0;
    QString type = "timestamp TYPE init";
    QString msg = "timestamp MSG init";
signals:

};

#endif // TIMESTAMP_H
