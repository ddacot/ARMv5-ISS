#include "uxtab.h"
#include <QDebug>
UXTAB::UXTAB(): Instruction()
{

}

void UXTAB::decode()
{
    Instruction::decode();

    Rd = Instruction::ExtractBits(assembledInstruction, 12, 15);
    Rm = Instruction::ExtractBits(assembledInstruction, 0, 3);
    rotate_imm = Instruction::ExtractBits(assembledInstruction, 10, 11);
    Rn = Instruction::ExtractBits(assembledInstruction, 16, 19);
    //dissassembledInstruction
}

void UXTAB::execute()
{
    int RdVal = cpu->regs->ReadWord(cpu->GET_REG_ADDR(Rd));
    int RmVal = cpu->regs->ReadWord(cpu->GET_REG_ADDR(Rm));
    int RnVal = cpu->regs->ReadWord(cpu->GET_REG_ADDR(Rn));
    if(Instruction::ExtractBits(assembledInstruction, 20, 27) == 0x6e)
    {
        cpu->regs->WriteWord(cpu->GET_REG_ADDR(Rd), RnVal + ((Instruction::cpu->rotr(RmVal, 8*rotate_imm) & 0x000000FF)));
    }
    else
    {
        int operand = (Instruction::cpu->rotr(RmVal, 8*rotate_imm) & 0x00FF00FF);
        int Rd0to15, Rd16to31;
        Rd0to15 = (Instruction::ExtractBits(RnVal, 0, 15) + Instruction::ExtractBits(operand, 0, 15)) & 0xFFFF;
        Rd16to31 = ((Instruction::ExtractBits(RnVal, 16, 31) + Instruction::ExtractBits(operand,16, 23)) << 16) & 0xFFFF0000;
        int RdFinal = Rd0to15 | Rd16to31;
        //qDebug() << RdFinal;
        cpu->regs->WriteWord(cpu->GET_REG_ADDR(Rd), RdFinal);

    }

    }
