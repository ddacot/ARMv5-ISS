#include "b.h"
#include <QDebug>
B::B() : Instruction ()
{

}

void B::decode()
{
    condition = Instruction::ExtractBits(this->assembledInstruction, 28, 31);
    L = Instruction::ExtractBits(this->assembledInstruction, 24, 24);
    signed_immed_24 = Instruction::ExtractBits(this->assembledInstruction, 0, 23);

    int result;

    int mostSignBit = (signed_immed_24 & 0x00800000);
    if((mostSignBit >> 23) && 1)
    {
        result = signed_immed_24 | 0x3F000000;
    }
    else
    {
        result = signed_immed_24;
    }

    result = result * 4;
    address = result + cpu->relativePC + 4;

    dissassembledInstruction = QString("%1 #%2").arg(L == 1 ? "bl" : "b", QString::number(address));
}

void B::execute()
{
    if(L == 1)
    {
        cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(R14), cpu->relativePC);
    }

    cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(R15), address);

}
