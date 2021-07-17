/*
 * @filename testcpu.h
 * @brief defines the testcpu class. Defines the unit test functions.
*/
#ifndef TESTCPU_H
#define TESTCPU_H
#include <computer.h>
class testcpu
{
public:
    testcpu();
    computer *cp;
    int testFetch();
    int testDecode();
    int testExecute();
};

#endif // TESTCPU_H
