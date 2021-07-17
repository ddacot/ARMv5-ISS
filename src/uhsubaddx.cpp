#include "uhsubaddx.h"

UHSUBADDX::UHSUBADDX(): Instruction()
{

}

void UHSUBADDX::decode()
{
    Instruction::decode();

    Rd = Instruction::ExtractBits(assembledInstruction, 12, 15);
    Rn = Instruction::ExtractBits(assembledInstruction, 16, 19);
    Rm = Instruction::ExtractBits(assembledInstruction, 0, 3);
    rotate_imm = Instruction::ExtractBits(assembledInstruction, 10, 11);
}

void UHSUBADDX::execute()
{
    //qDebug() << "yo";
    int RdVal = cpu->regs->ReadWord(cpu->GET_REG_ADDR(Rd));
    int RmVal = cpu->regs->ReadWord(cpu->GET_REG_ADDR(Rm));
    int RnVal = cpu->regs->ReadWord(cpu->GET_REG_ADDR(Rn));

    uint Rd0to15, Rd16to31;
    uint diff = Instruction::ExtractBits(RnVal, 16, 31) - Instruction::ExtractBits(RmVal, 0, 15);
    Rd16to31 = Instruction::ExtractBits(diff, 1, 16)<<16;

    uint sum = Instruction::ExtractBits(RnVal, 0, 15) + Instruction::ExtractBits(RmVal, 16, 31);
    Rd0to15 = Instruction::ExtractBits(sum, 1, 16);

    int RdFinal = Rd0to15 | Rd16to31;
    cpu->regs->WriteWord(cpu->GET_REG_ADDR(Rd), RdFinal);
}
