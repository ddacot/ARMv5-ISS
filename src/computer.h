#ifndef COMPUTER_H
#define COMPUTER_H

#include "cpu.h"
#include "memory.h"
#include <QShortcut>
class computer: public QObject {
    Q_OBJECT
public:

    uint32_t REG_SIZE = 4;
    uint32_t MAX_MEM_SIZE = 1024000;
    uint32_t RAM_SIZE = 32768;
    uint32_t REGS_NR = 23;

    std::vector<uint32_t> breakpoints;

    QString traceRowFormat = "%1 %2 %3 %4 %5 0=%6 1=%7 2=%8 3=%9 4=%10 5=%11 6=%12 7=%13 8=%14 9=%15 10=%16 11=%17 12=%18 13=%19 14=%20\n";
    std::fstream *traceFilePointer;
    bool traceEnable = 0, traceall = 0, osPresent = 0;
    memory ram;
    memory flags;
    memory regs;
    cpu cpu;

    computer();
    void initiateThread();
    void run();
    int step();
    QString GetTrace();
    void restart();
    void initRegs();

signals:
    void finished();
};

#endif // COMPUTER_H
