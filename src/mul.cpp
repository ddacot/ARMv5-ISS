#include "mul.h"
#include <QtDebug>
MUL::MUL() : DataProcessingInstruction ()
{

}

void MUL::decode()
{
    DataProcessingInstruction::decode();
    Rd = Instruction::ExtractBits(assembledInstruction, 16, 19);
    Rm = Instruction::ExtractBits(assembledInstruction, 0, 3);
    Rs = Instruction::ExtractBits(assembledInstruction, 8, 11);

    switch (AddressingModeType)
    {
    case AddressingMode::Register:
        RsVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rs));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));

        if(Rs == 15) RsVal += 4;
        if(Rm == 15) RmVal += 4;

        result = (int32_t)(RsVal * RmVal);

        dissassembledInstruction = QString("%1 %2, %3, %4").arg("mul", regNames[Rd], regNames[Rm], regNames[Rs]);
        break;
    }
}

void MUL::execute()
{
    switch (AddressingModeType)
    {
    case AddressingMode::Register:

        Instruction::cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), result);
        //qDebug() <<QString::number(RsVal) << " " << QString::number(RmVal) <<" " <<QString::number(cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rd)));
        break;
    }
}
