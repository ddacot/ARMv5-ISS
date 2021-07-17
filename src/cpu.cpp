#include "cpu.h"
#include "instruction.h"
#include "getinstructioninstance.h"
#include "mov.h"
#include <QTimer>
#include <cstdint>
#include<stdio.h>
//#include <qdebug>
#define INT_BITS 32

cpu::cpu()
{

}

int cpu::GET_REG_ADDR(int NR_REG)
{
    if((NR_REG >= 0 && NR_REG <= 12) || NR_REG >= 15)
    {
        return NR_REG * 4;
    }
    else
    {
        switch (this->mode)
        {
            case CPU_MODE::SYS:
                if(NR_REG == 13)
                    return R13_UM * 4;
                if(NR_REG == 14)
                    return R14_UM * 4;
            break;

            case CPU_MODE::SVC:
                if(NR_REG == 13)
                    return R13_SVC * 4;
                if(NR_REG == 14)
                    return R14_SVC * 4;
            break;

            case CPU_MODE::IRQ:
                if(NR_REG == 13)
                    return R13_IRQ *4;
                if(NR_REG == 14)
                    return R14_IRQ* 4;
            break;

            default:
                if(NR_REG == 13)
                    return R13_UM* 4;
                if(NR_REG == 14)
                    return R14_UM*4;
            break;
        }
    }
}

void cpu::fetch()
{
    currentInstruction = GetInstructionInstance::GetInstruction(this->ram->ReadWord(regs->ReadWord(this->GET_REG_ADDR(R15))));

}
void cpu::decode()
{
    currentInstruction->decode();
}

void cpu::execute()
{
    bool execute = false;
    int flags = this->flags->ReadWord(0);
    int N,Z,C,V;
    N = this->regs->TestFlag(this->GET_REG_ADDR(CPSR), N_bit);
    Z = this->regs->TestFlag(this->GET_REG_ADDR(CPSR), Z_bit);
    C = this->regs->TestFlag(this->GET_REG_ADDR(CPSR), C_bit);
    V = this->regs->TestFlag(this->GET_REG_ADDR(CPSR), V_bit);
    //qDebug() << currentInstruction->condition;
    switch(currentInstruction->condition)
    {
    case (0): //EQ
       // qDebug() << "Got Ito case 0";
        if(Z == 1)
        {
            execute = true;
        }
        break;
    case (1): //NE
        if(Z == 0)
        {
            execute = true;
        }
        break;
    case (2): //CS/HS
        if(C==1)
        {
            execute = true;
        }
        break;
    case (3): //CC/LO
        if(C==0)
        {
            execute = true;
        }
        break;
    case (4): //MI
        if(N==1)
        {
            execute = true;
        }
        break;
    case (5): //PL
        if(N==0)
        {
            execute = true;
        }
        break;
    case 6: //VS
        if(V==1)
        {
            execute = true;
        }
        break;
    case 7: // VC
        if(V==0)
        {
            execute = true;
        }
        break;
    case 8: //HI
        if(C == 1 && Z == 0)
        {
            execute = true;
        }
        break;
    case 9: //LS
        if(C == 0 || Z == 1)
        {
            execute = true;
        }
        break;
    case 10: //GE
        if(N == V)
        {
            execute = true;
        }
        break;
    case 11://:T
        if(N!=V)
        {
            execute = true;
        }
        break;
    case 12: //GT
        if(Z == 0 && N == V)
        {
            execute = true;
        }
        break;
    case 13: //LE
        if(Z==1 || N != V)
        {
            execute = true;
        }
        break;
    case 14: //AL
        execute = true;
        break;
    case 15:
        break;



    }
    //qDebug() << execute;
    if(execute)
    {
        currentInstruction->execute();
    }
}

/*Function to left rotate n by d bits*/
int cpu::rotl(int n, unsigned int d)
{
   return (n << d)|(n >> (INT_BITS - d));
}

/*Function to right rotate n by d bits*/
int cpu::rotr(int n, unsigned int d)
{
   return (n >> d)|(n << (INT_BITS - d));
}
