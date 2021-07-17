#include "mrs.h"

MRS::MRS() : Instruction ()
{

}

void MRS::decode()
{
    Instruction::decode();
    R = Instruction::ExtractBits(this->assembledInstruction, 22,22);
    Rd = Instruction::ExtractBits(this->assembledInstruction, 12,15);

    if(R==1)
        dissassembledInstruction = QString("%1 %2, %3").arg("mrs", regNames[Rd],"CPSR");
    else
        dissassembledInstruction = QString("%1 %2, %3").arg("mrs", regNames[Rd], "SPSR");
    //dissassembledInstruction = QString("%1 %2, %3").arg("mrs", regNames[Rn], regNames[Rm]);

}

void MRS::execute()
{
    if(R == 1)
    {
        switch (Instruction::cpu->mode) {
        case CPU_MODE::IRQ:
            cpu->regs->WriteWord(cpu->GET_REG_ADDR(Rd), Instruction::cpu->regs->ReadWord(cpu->GET_REG_ADDR(SPSR_IRQ)));
            break;
        case CPU_MODE::SVC:
            cpu->regs->WriteWord(cpu->GET_REG_ADDR(Rd), Instruction::cpu->regs->ReadWord(cpu->GET_REG_ADDR(SPSR_SVC)));
        }
    }
    else
    {
        cpu->regs->WriteWord(cpu->GET_REG_ADDR(Rd), Instruction::cpu->regs->ReadWord(cpu->GET_REG_ADDR(CPSR)));
    }
}
