#include "mythread.h"

MyThread::MyThread(computer *comp)
{
    this->comp = comp;
}

void MyThread::run()
{
    this->comp->run();
}
