#include "computer.h"
#include "worker.h"
#include "instruction.h"
#include <QThread>
#include <QDebug>
#include <fstream>

cpu* Instruction::cpu = NULL;

computer::computer()
{
    ram.SetUpMemory(RAM_SIZE);
    flags.SetUpMemory(REG_SIZE);
    regs.SetUpMemory(REGS_NR * REG_SIZE);
    ram.cpu = &cpu;

    cpu.flags = &flags;
    cpu.ram = &ram;
    cpu.regs = &regs;
    cpu.currentComputer = this;
    Instruction::cpu = &cpu;

    cpu.regs->SetFlag(cpu.GET_REG_ADDR(CPSR), I_bit, 1);
}

void computer::run()
{
    while(!cpu.HLT && step() && !(std::find(breakpoints.begin(), breakpoints.end(), cpu.regs->ReadWord(R15)) != breakpoints.end()))
    {

    }

    cpu.HLT = 0;
}

QString computer::GetTrace()
{
    QString stepCounterStr = QString::number(cpu.stepCounter-1, 10).rightJustified(6, '0').toUpper();
    QString programCounterStr = QString::number(cpu.relativePC -4, 16).rightJustified(8, '0').toUpper();
    QString ramChecksumStr = QString::number((uint32_t)this->ram.calculateChecksum(), 16).rightJustified(8, '0').toUpper();
    QString nzcfStr = QString::number(((uint8_t)this->regs.ReadByte(cpu.GET_REG_ADDR(CPSR)+3))>>4, 2).rightJustified(4, '0');
    QString modeStr;
    if(cpu.mode == CPU_MODE::IRQ)
        modeStr = "IRQ";
    else if(cpu.mode == CPU_MODE::SVC)
        modeStr = "SVC";
    else if(cpu.mode == CPU_MODE::SYS)
        modeStr = "SYS";
   QString R0STR = QString::number((uint32_t)this->regs.ReadWord(cpu.GET_REG_ADDR(R0)), 16).rightJustified(8, '0').toUpper();
    QString R1STR = QString::number((uint32_t)this->regs.ReadWord(cpu.GET_REG_ADDR(R1)), 16).rightJustified(8, '0').toUpper();
    QString R2STR = QString::number((uint32_t)this->regs.ReadWord(cpu.GET_REG_ADDR(R2)), 16).rightJustified(8, '0').toUpper();
    QString R3STR = QString::number((uint32_t)this->regs.ReadWord(cpu.GET_REG_ADDR(R3)), 16).rightJustified(8, '0').toUpper();
    QString R4STR = QString::number((uint32_t)this->regs.ReadWord(cpu.GET_REG_ADDR(R4)), 16).rightJustified(8, '0').toUpper();
    QString R5STR = QString::number((uint32_t)this->regs.ReadWord(cpu.GET_REG_ADDR(R5)), 16).rightJustified(8, '0').toUpper();
    QString R6STR = QString::number((uint32_t)this->regs.ReadWord(cpu.GET_REG_ADDR(R6)), 16).rightJustified(8, '0').toUpper();
    QString R7STR = QString::number((uint32_t)this->regs.ReadWord(cpu.GET_REG_ADDR(R7)), 16).rightJustified(8, '0').toUpper();
    QString R8STR = QString::number((uint32_t)this->regs.ReadWord(cpu.GET_REG_ADDR(R8)), 16).rightJustified(8, '0').toUpper();
    QString R9STR = QString::number((uint32_t)this->regs.ReadWord(cpu.GET_REG_ADDR(R9)), 16).rightJustified(8, '0').toUpper();
    QString R10STR = QString::number((uint32_t)this->regs.ReadWord(cpu.GET_REG_ADDR(R10)), 16).rightJustified(8, '0').toUpper();
    QString R11STR = QString::number((uint32_t)this->regs.ReadWord(cpu.GET_REG_ADDR(R11)), 16).rightJustified(8, '0').toUpper();
    QString R12STR = QString::number((uint32_t)this->regs.ReadWord(cpu.GET_REG_ADDR(R12)), 16).rightJustified(8, '0').toUpper();
    QString R13STR = QString::number((uint32_t)this->regs.ReadWord(cpu.GET_REG_ADDR(R13)), 16).rightJustified(8, '0').toUpper();
    QString R14STR = QString::number((uint32_t)this->regs.ReadWord(cpu.GET_REG_ADDR(R14)), 16).rightJustified(8, '0').toUpper();

    QString row = traceRowFormat.arg(stepCounterStr,
                                     programCounterStr,
                                     ramChecksumStr,
                                     nzcfStr,
                                     modeStr,
                                     R0STR,
                                     R1STR,
                                     R2STR,
                                     R3STR);
    row = row.arg(R4STR,
                  R5STR,
                  R6STR,
                  R7STR,
                  R8STR,
                  R9STR,
                  R10STR,
                  R11STR,
                  R12STR);

   row = row.arg(R13STR,
                 R14STR);
    return row;
}

int computer::step()
{
    cpu.fetch();
    cpu.regs->WriteWord(cpu.GET_REG_ADDR(R15), (cpu.regs->ReadWord(cpu.GET_REG_ADDR(R15))) + 4);
    cpu.relativePC = (cpu.regs->ReadWord(cpu.GET_REG_ADDR(R15)));
    cpu.stepCounter++;

    if(cpu.currentInstruction != NULL)
    {
        cpu.decode();
        cpu.execute();
    }
    if(traceEnable)
    {
        if(!traceall)
        {
            if(cpu.mode == CPU_MODE::SYS)
            {
                if(!osPresent)
                {
                    (*traceFilePointer) << GetTrace().toStdString();
                }
                else
                {
                    if(cpu.relativePC - 4 >= cpu.ENTRY_POINT_ADDR)
                    {
                        (*traceFilePointer) << GetTrace().toStdString();
                    }
                }
            }
        }
        else
        {
            (*traceFilePointer) << GetTrace().toStdString();
        }
    }
    if(cpu.IRQ_flag && Instruction::ExtractBits(cpu.regs->ReadWord(cpu.GET_REG_ADDR(CPSR)), I_bit,I_bit) == 0)
    {
        //qDebug() << cpu.regs->ReadWord(cpu.GET_REG_ADDR(CPSR));
        cpu.IRQ_flag = false;
        //1. Save CPSR to Supervisor's SPSR
        cpu.regs->WriteWord(cpu.GET_REG_ADDR(SPSR_IRQ), cpu.regs->ReadWord(cpu.GET_REG_ADDR(CPSR)));

        //2. save next instruction addr to Sup's Link Reg (R14)
        cpu.regs->WriteWord(cpu.GET_REG_ADDR(R14_IRQ), cpu.regs->ReadWord(cpu.GET_REG_ADDR(R15))+8);

        //3. Modify CPSR to Supervisor, disable interrupts
        uint32_t cpsr = cpu.regs->ReadWord(cpu.GET_REG_ADDR(CPSR));

        cpsr = (cpsr & 0xFFFFFFE0) | 0b10010; //IRQ
        cpsr = (cpsr | 0x00000080); //disable interrupts

        cpu.regs->WriteWord(cpu.GET_REG_ADDR(CPSR), cpsr);

        cpu.mode = CPU_MODE::IRQ;
        //qDebug() << "STEP: Change mode to IRQ";
        //4.branch to 0x8;
        cpu.regs->WriteWord(cpu.GET_REG_ADDR(R15), 0x00000018);

        //cpu.mode = CPU_MODE::SYS;

    }
    return 1;
}

void computer::initRegs()
{
    cpu.keyboardInput.clear();
    //disabling interrupts;
    cpu.regs->SetFlag(cpu.GET_REG_ADDR(CPSR), I_bit, 1);
    uint32_t cpsr = cpu.regs->ReadWord(cpu.GET_REG_ADDR(CPSR));
    cpsr = (cpsr & 0xFFFFFFEC) | 0b10011; //Supervisor
    cpu.regs->WriteWord(cpu.GET_REG_ADDR(CPSR), cpsr);

    if(cpu.ram->ReadByte(0) != 0)
    {
        //qDebug() << "SWI: Change mode to SVC;
        osPresent = true;
        cpu.mode = CPU_MODE::SVC;
        cpu.regs->WriteWord(cpu.GET_REG_ADDR(R15), 0);
    }
    else
    {
        osPresent = false;
        cpu.mode = CPU_MODE::SYS;
        cpu.regs->WriteWord(cpu.GET_REG_ADDR(R13), cpu.STACK_ADDR);
        cpu.regs->WriteWord(cpu.GET_REG_ADDR(R15), cpu.ENTRY_POINT_ADDR);
    }

}

void computer::restart()
{
    ram.reset();
    flags.reset();
    regs.reset();

    cpu.stepCounter = 1;
    cpu.HLT = 0;
}
