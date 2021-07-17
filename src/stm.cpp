#include "stm.h"
#include <QDebug>
STM::STM() : LoadStoreInstruction ()
{

}

void STM::decode()
{
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
        dissassembledInstruction = dissassembledInstruction.arg("stmfd", regNames[Rn], "!", RL);
    else
        dissassembledInstruction = dissassembledInstruction.arg("stmfd", regNames[Rn], RL);

}
void STM::execute()
{

    switch (this->AddressingModeType) {
    case AddressingMode::StackFullDescending:
        RnVal = RnVal - (4*nrOfRegisters);

        for(int i = 0; i <= 15; i++)
        {
            if((register_list & (1 << i) && 1))
            {
                cpu->ram->WriteWord(RnVal, cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(i)));
                RnVal+=4;
            }
        }

        if(W == 1)
        {
            cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rn), cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn)) - (4*nrOfRegisters));

        }

        break;

    }
}
