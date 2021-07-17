/*
 * @filename testcomputer.cpp
 * @brief the following file implements unit tests for the Computer class
*/
#include "testcomputer.h"
#include "computer.h"
#include <cassert>
#include <QDebug>
#include <QTest>

testcomputer::testcomputer()
{
    comp = new computer();

    testRun();
    testRestart();

}

void testcomputer::testRun()
{
    comp->step();
    assert(comp->regs.ReadWord(R15) == 4);

    comp->step();
    assert(comp->regs.ReadWord(R15) == 8);
}

void testcomputer::testRestart()
{
    comp->restart();
    assert(comp->regs.ReadWord(R15) == 0);
    assert(comp->cpu.HLT == false);

}
