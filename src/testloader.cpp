/*
 * @filename testloaer.cpp
 * @brief the following file implements unit tests for the Loader class
*/

#include "testloader.h"
#include "computer.h"
#include <cassert>
#include <QDebug>
#include <QTest>
TestLOADER::TestLOADER()
{
    l = new Loader();
    qDebug() << "Testing LOADER..";
    TestIsElf();
}

void TestLOADER::TestIsElf()
{
   //computer computer;
   l->elfFileName = QCoreApplication::applicationDirPath() +  "/" + "test2.exe";
   l->ReadElf();

   assert(l->isElf(&l->elfHeader) == true);
   assert(l->Computer.ram.calculateChecksum() == 536864433);

}
