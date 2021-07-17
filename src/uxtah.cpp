#include "uxtah.h"

UXTAH::UXTAH(): Instruction()
{

}

void UXTAH::decode()
{
    Instruction::decode();

    Rd = Instruction::ExtractBits(assembledInstruction, 12, 15);
    Rm = Instruction::ExtractBits(assembledInstruction, 0, 3);
    rotate_imm = Instruction::ExtractBits(assembledInstruction, 10, 11);
    Rn = Instruction::ExtractBits(assembledInstruction, 16, 19);
    //dissassembledInstruction
}

void UXTAH::execute()
{
    int RdVal = cpu->regs->ReadWord(cpu->GET_REG_ADDR(Rd));
    int RmVal = cpu->regs->ReadWord(cpu->GET_REG_ADDR(Rm));
    int RnVal = cpu->regs->ReadWord(cpu->GET_REG_ADDR(Rn));

    cpu->regs->WriteWord(cpu->GET_REG_ADDR(Rd), RnVal + (Instruction::cpu->rotr(RmVal, 8*rotate_imm) & 0x0000FFFF));
}
