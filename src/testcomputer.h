/*
 * @filename testcomputer.h
 * @brief defines the testcomputer class. Defines the unit test functions.
*/
#ifndef TESTCOMPUTER_H
#define TESTCOMPUTER_H
#include <computer.h>

class testcomputer
{
public:
    testcomputer();
    computer *comp;
    void testRun();
    int testStep();
    void testRestart();
};

#endif // TESTCOMPUTER_H
