#include "ldm.h"
#include <QDebug>
LDM::LDM() : LoadStoreInstruction ()
{

}

void LDM::decode()
{
    Instruction::decode();
    LoadStoreInstruction::decode();

    RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
    register_list = Instruction::ExtractBits(assembledInstruction, 0, 15);
    nrOfRegisters = countSetBits(register_list);

    dissassembledInstruction = (W == 1 ? QString("%1 %2%3, {%4}"): QString("%1 %2, {%3}"));
    QString RL;
    for(int i = 0; i < 16; i++)
    {
        if((register_list & (1 << i)) && 1)
        {
            RL += regNames[i] + ",";
        }

    }
    RL.remove(RL.size()-1,1);

    if(W==1)
        dissassembledInstruction = dissassembledInstruction.arg("ldmfd", regNames[Rn], "!", RL);
    else
        dissassembledInstruction = dissassembledInstruction.arg("ldmfd", regNames[Rn], RL);

}

void LDM::execute()
{

    int startAddress, endAddress;
    //qDebug() << QString::number(cpu->ram->ReadWord(RnVal));
    switch (this->AddressingModeType) {
    case AddressingMode::StackFullDescending:

        for(int i = 0; i < 16; i++)
        {
            if((register_list & (1 << i)) && 1)
            {
                cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(i), cpu->ram->ReadWord(RnVal));
                RnVal+=4;
            }
        }

        if(W == 1)
        {
            cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rn), RnVal);
        }

        break;

    }
}
