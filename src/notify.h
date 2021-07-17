#ifndef NOTIFY_H
#define NOTIFY_H

#include <QObject>

class Notify :public QObject
{
    Q_OBJECT
public:
    Notify();
    //~Notify();

signals:
    void printToConsole(QChar c);

};

#endif // NOTIFY_H
