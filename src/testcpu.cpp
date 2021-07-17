#include "testcpu.h"
/*
 * @filename testcpu.cpp
 * @brief the following file implements unit tests for the Cpu class
*/
#include <cassert>
#include <QDebug>
#include <QTest>
#include <computer.h>
testcpu::testcpu()
{

    cp = new computer();
    //testFetch();
}


