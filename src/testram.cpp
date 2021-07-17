/*
 * @filename testRam.cpp
 * @brief the following file implements unit tests for the RAM class.
*/

#include "testram.h"
#include <cassert>
#include "memory.h"
#include "computer.h"
#include <QDebug>
#include <QTest>

TestRAM::TestRAM()
{
    computer computer;

    qDebug() << "Testing RAM";

    RAM = &computer.ram;

    //TestWriteAndReadWord();
    //TestWriteAndReadByte();
    //TestWriteAndReadHalfWord();
    TestTestFlags();
    TestSetFlags();
    //TestExtractBits();
}

void TestRAM::TestWriteAndReadWord()
{
    uint32_t num = 0xAABBCCDD;

    RAM->WriteWord(0,num);

    QVERIFY(RAM->ReadByte(0) == 0xDD);
    assert(RAM->ReadByte(0) == 0xDD);
    assert(RAM->ReadByte(1) == 0xCC);
    assert(RAM->ReadByte(2) == 0xBB);
    assert(RAM->ReadByte(3) == 0xAA);

    num = 0xABCDEFAB;

    RAM->WriteWord(0,num);

    assert(RAM->ReadByte(0) == 0xAB);
    assert(RAM->ReadByte(1) == 0xEF);
    assert(RAM->ReadByte(2) == 0xCD);
    assert(RAM->ReadByte(3) == 0xAB);
}

void TestRAM::TestWriteAndReadByte()
{
    RAM->WriteByte(0, 8);
    assert(RAM->ReadByte(0) == 8);

    RAM->WriteByte(1, 2);
    assert(RAM->ReadByte(1) == 2);

    RAM->WriteByte(524, 22);
    assert(RAM->ReadByte(524) == 22);

    RAM->WriteByte(9999, 122);
    assert(RAM->ReadByte(9999) == 122);

}

void TestRAM::TestWriteAndReadHalfWord()
{
    uint16_t num = 0xAA22;
    RAM->WriteHalfWord(0, num);
    assert((int)RAM->ReadHalfWord(0) == 0xAA22);

    num = 0xABCD;
    RAM->WriteHalfWord(0, num);
    assert((int)RAM->ReadHalfWord(0) == 0xABCD);

}

void TestRAM::TestTestFlags()
{
    RAM->WriteWord(0, 0x80000001);
    assert(RAM->TestFlag(0,0) == true);

    RAM->WriteWord(0, 0x00000001);
    assert(RAM->TestFlag(0,0) == true);
    assert(RAM->TestFlag(2,1) == false);
}

void TestRAM::TestSetFlags()
{
   uint32_t num = 0;
   RAM->WriteWord(0,num);
   RAM->SetFlag(0,0,1);
   assert(RAM->TestFlag(0,0) == 1);

   RAM->SetFlag(0,0,0);
   assert(RAM->TestFlag(0,0) == 0);
}

void TestRAM::TestExtractBits()
{
    assert(RAM->ExtractBits(0xb5,1,3) == 0x04);
}


