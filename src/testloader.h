/*
 * @filename testloader.h
 * @brief defines the testloader class. Defines the unit test functions.
*/
#ifndef TESTLOADER_H
#define TESTLOADER_H
#include "loader.h"

class TestLOADER
{
public:
    //pointer to the Loader instance
    Loader *l;

    void TestIsElf();
    TestLOADER();
};

#endif // TESTLOADER_H
