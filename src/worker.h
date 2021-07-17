#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include "computer.h"
class Worker: public QObject {
    Q_OBJECT
public:
    Worker(computer *comp);
    ~Worker();

public slots:
    void run();
    void step();
signals:
    void finished();
    void error(QString err);
private:
    computer *comp;
};

#endif // WORKER_H
