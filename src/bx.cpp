#include "bx.h"
#include <QDebug>
BX::BX() : Instruction()
{

}

void BX::decode()
{
    Instruction::decode();
    condition = Instruction::ExtractBits(this->assembledInstruction, 28, 31);
}

void BX::execute()
{
    int PcVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(R15)) + 4;
    Rm = Instruction::ExtractBits(this->assembledInstruction, 0, 3);
    uint RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));
    uint32_t address;

    if(Rm == 15)
    {
        address = PcVal;
    }
    else
    {
        address = (RmVal & 0xFFFFFFFE);
    }

    //qDebug() << address;
    cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(R15), address);

    dissassembledInstruction = QString("%1 %2").arg("bx", regNames[Rm]);
}
