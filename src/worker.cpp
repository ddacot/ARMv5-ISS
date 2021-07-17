/*
 * @filename worker.cpp
 * @brief the following file implements the functions for the worker class.
 * Implements multithreading.
*/

#include "worker.h"
#include <QThread>
#include <QDebug>
Worker::Worker(computer *comp)
{
    this->comp = comp;
}

Worker::~Worker()
{

}
void Worker::run()
{
    this->comp->run();
    emit this->finished();
}

void Worker::step()
{
    this->comp->step();
    emit this->finished();
}
