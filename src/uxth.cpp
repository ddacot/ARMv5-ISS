#include "uxth.h"
#include <QDebug>
UXTH::UXTH() : Instruction ()
{

}

void UXTH::decode()
{
    Instruction::decode();

    Rd = Instruction::ExtractBits(assembledInstruction, 12, 15);
    Rm = Instruction::ExtractBits(assembledInstruction, 0, 3);
    rotate_imm = Instruction::ExtractBits(assembledInstruction, 10, 11);

}

void UXTH::execute()
{
    int RdVal = cpu->regs->ReadWord(cpu->GET_REG_ADDR(Rd));
    int RmVal = cpu->regs->ReadWord(cpu->GET_REG_ADDR(Rm));
    cpu->regs->WriteWord(cpu->GET_REG_ADDR(Rd), Instruction::cpu->rotr(RmVal, 8*rotate_imm) & 0x0000FFFF);

}
