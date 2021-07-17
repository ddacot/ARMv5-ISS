#include "swi.h"
#include <QThread>
#include "worker.h"
#include <QDebug>
SWI::SWI(): Instruction ()
{

}

void SWI::decode()
{
    Instruction::decode();
    immed_24 = Instruction::ExtractBits(this->assembledInstruction, 0, 23);
    dissassembledInstruction = QString("%1 #%2").arg("swi", QString::number(immed_24));
}

void SWI::execute()
{
    if(immed_24 == 0x11)
    {
        Instruction::cpu->HLT = 1;
    }
    else
    {

        //1. Save CPSR to Supervisor's SPSR
        cpu->regs->WriteWord(cpu->GET_REG_ADDR(SPSR_SVC), cpu->regs->ReadWord(cpu->GET_REG_ADDR(CPSR)));

        //2. save next instruction addr to Sup's Link Reg (R14)
        cpu->regs->WriteWord(cpu->GET_REG_ADDR(R14_SVC), cpu->regs->ReadWord(cpu->GET_REG_ADDR(R15)));

        //3. Modify CPSR to Supervisor, disable interrupts
        uint32_t cpsr = cpu->regs->ReadWord(cpu->GET_REG_ADDR(CPSR));
        cpsr = (cpsr & 0xFFFFFFE0) | 0b10011; //Supervisor
        cpsr = (cpsr | 0x00000080); //disable interrupts

        cpu->regs->WriteWord(cpu->GET_REG_ADDR(CPSR), cpsr);

        cpu->mode = CPU_MODE::SVC;
        //qDebug() << "SWI: Change mode to SVC";
        //4.branch to 0x8;
        cpu->regs->WriteWord(cpu->GET_REG_ADDR(R15), 8);

    }
}

