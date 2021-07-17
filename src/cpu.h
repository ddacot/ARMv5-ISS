#ifndef CPU_H
#define CPU_H

//#include "computer.h"
#include "memory.h"
#include "notify.h"
#include <QQueue>

/* CPSR */
#define N_bit 31
#define Z_bit 30
#define C_bit 29
#define V_bit 28
#define I_bit 7

#define N_flag_mask 0x80000000
#define Z_flag_mask 0x40000000
#define C_flag_mask 0x20000000
#define V_flag_mask 0x10000000
#define I_flag_mask 0x00000080
/* END CPSR */


/* REGISTERS */
#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define R4 4
#define R5 5
#define R6 6
#define R7 7
#define R8 8
#define R9 9
#define R10 10
#define R11 11
#define R12 12
#define R13 13
#define R14 14
#define R15 15
#define CPSR 16

/*user mode */
#define R13_UM 13
#define R14_UM 14

/* Supervisor Mode */
#define R13_SVC 17
#define R14_SVC 18
#define SPSR_SVC 19

/* IRQ Mode */
#define R13_IRQ 20
#define R14_IRQ 21
#define SPSR_IRQ 22
/* END REGISTERS */

enum class CPU_MODE
{
    SYS,
    SVC,
    IRQ
};

class cpu
{
public:

    class Instruction *currentInstruction;
    class computer *currentComputer;
    class Notify *notifier;

    memory *ram;
    memory *stack;
    memory *flags;
    memory *regs;

    bool HLT = 0;
    bool displayChar = false;
    bool IRQ_flag = false;
    int stepCounter = 1;
    int relativePC;

    int ENTRY_POINT_ADDR;
    int STACK_ADDR;

    CPU_MODE mode = CPU_MODE::SYS;
    QQueue<char> keyboardInput;
    char lastCharacter = '\r';

    void fetch();
    void decode();
    void execute();

    int GET_REG_ADDR(int NR_REG);
    int rotl(int n, unsigned int d);
    int rotr(int n, unsigned int d);

    cpu();

};

#endif // CPU_H
