/*
 * @filename main.cpp
 * @brief This file sets up the program. Contains the entry point of the program.
*/

#include "loader.h"
#include <QApplication>
#include "options.h"
#include "memory.h"
#include "include/CLI11.hpp"
#include <QCommandLineParser>
#include "log.h"
#include <QtGlobal>
#include <QDebug>
#include <cassert>
#include "testloader.h"
#include "testram.h"
#include "testinstructions.h"
#include "testcomputer.h"
#include "testcpu.h"
int main(int argc, char *argv[])
{
    qInstallMessageHandler(log::MessageOutput);

    QApplication a(argc, argv);
    Loader w;
    w.show();

    //pass loader instance to the static log class.
    log::lg = &w;

    //instantiate options class.
    Options CLOptions;

    //create parse object
    CLOptions.parse(&a);

    //extract values from command line;
    CLOptions.extractValues();

    //Check if "Unit Tests" flag is set
    if(CLOptions.test)
    {
        qDebug() << "Testing modules.. ";

        //TestLOADER loaderTest;
        //TestRAM ramTest;
        //testcomputer computerTest;
        //testcpu cpuTest;


        testinstructions testInstr;
        //qDebug() << testInstr.comp->regs.ReadWord(GET_REG_ADDR(R15));
        qDebug() << "Done testing modules..";

        exit(0);
        w.close();
        a.quit();
        a.exit();
    }

    w.Computer.RAM_SIZE = CLOptions.MEM_SIZE;
    w.elfFileName = CLOptions.elfFileName;
    log::toFile = CLOptions.debugToFile;
    w.Computer.traceall = CLOptions.traceallB;

    w.Computer.restart();
    //read the Elf file into RAM
    if(w.ReadElf())
    {
        qDebug() << "Could not parse the ELF file.";
    }
    else
    {
        w.startPC = w.Computer.regs.ReadWord(w.Computer.cpu.GET_REG_ADDR(R15)) + 4;
        w.Computer.initRegs();
    }

    w.UpdateUi();


    if(CLOptions.loadPresent && CLOptions.execOption)
    {
        w.Computer.run();

        exit(0);
        w.close();
        a.quit();
        a.exit();
    }

    return a.exec();
}
