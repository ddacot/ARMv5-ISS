#ifndef TESTINSTRUCTIONS_H
#define TESTINSTRUCTIONS_H
#include "computer.h"

class testinstructions
{
public:
    computer *comp;
    testinstructions();
    void testMOV();
    void testADD();
    void testMVN();
    void testSUB();
    void testRSB();
    void testMUL();
    void testAND();
    void testORR();
    void testEOR();
    void testBIC();
    void testSTR();
    void testLDR();
    void testSTM();
    void testLDM();
    void testCMP();

    void testB();
    void testBX();

    void testMRS();
    void testMSR();
    void testMOVS();

    void testUXTH();
    void testUXTB();
    void testUXTAH();
    void testUXTAB();
    void testUHADD();
    void testUHADDSUBX();
    void testUHSUB();


};

#endif // TESTINSTRUCTIONS_H
