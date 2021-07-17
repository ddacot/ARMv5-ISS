/*
 * @filename testram.h
 * @brief defines the testram class. Defines ram unit test functions.
*/
#ifndef TESTRAM_H
#define TESTRAM_H
#include "memory.h"

class TestRAM
{
public:

    //pointer to the ram instance.
    memory *RAM;

    void TestWriteAndReadWord();
    void TestWriteAndReadByte();
    void TestWriteAndReadHalfWord();
    void TestTestFlags();
    void TestSetFlags();
    void TestExtractBits();
    void TestcalculateChecksum();
    TestRAM();
};

#endif // TESTRAM_H
