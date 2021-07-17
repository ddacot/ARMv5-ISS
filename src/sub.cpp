#include "sub.h"
#include "dataprocessinginstruction.h"
#include <QDebug>
SUB::SUB() : DataProcessingInstruction()
{

}

void SUB::execute()
{
    int RnVal, RmVal, RsVal;
    switch (AddressingModeType)
    {
    case AddressingMode::Immediate:

        Instruction::cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), result);

    break;

    case AddressingMode::Register:

        Instruction::cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd),result);

        break;

    case AddressingMode::LSLImmediate:


        Instruction::cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), result);
        //qDebug() << QString::number(cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rd)));

        break;

    case AddressingMode::LSLRegister:


        Instruction::cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), result);
        //qDebug() << QString::number(cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rd)));
        break;

    case AddressingMode::LSRImmediate:


        Instruction::cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), result);

        break;

    case AddressingMode::LSRRegister:



        Instruction::cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), result);

        break;

    case AddressingMode::ASRImmediate:


        Instruction::cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), result);
        break;

    case AddressingMode::ASRRegister:



        Instruction::cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), result);

        break;
    case AddressingMode::RORImmediate:


        if(shift_imm > 0)
        {
            Instruction::cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), result);
        }
        break;
    case AddressingMode::RORRegister:


        Instruction::cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), result);
        break;

    }
}

void SUB::decode()
{
    DataProcessingInstruction::decode();

    int RnVal, RmVal, RsVal;
    switch (AddressingModeType)
    {
    case AddressingMode::Immediate:
        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));

        if(Rn == 15) RnVal += 4;

        result = RnVal - Instruction::cpu->rotr(immed_8, 2*rotate_imm);
        dissassembledInstruction = QString("%1 %2,%3,#%4").arg("sub", regNames[Rd], regNames[Rn], QString::number(Instruction::cpu->rotr(immed_8, 2*rotate_imm)));

    break;

    case AddressingMode::Register:
        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;

        result = RnVal - RmVal;
        dissassembledInstruction = QString("%1 %2, %3, %3, %4").arg("sub", regNames[Rd], regNames[Rn], regNames[Rm]);

        //qDebug() << QString::number(cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rd)));

        break;

    case AddressingMode::LSLImmediate:
        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;

        result = RnVal - (((uint32_t)RmVal) << shift_imm);
        dissassembledInstruction = QString("%1 %2, %3, %4, #%5").arg("sub", regNames[Rd], regNames[Rn], "LSL", QString::number(shift_imm));

        //qDebug() << QString::number(cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rd)));

        break;

    case AddressingMode::LSLRegister:
        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));
        RsVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rs));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;
        if(Rs == 15) RsVal += 4;

        result = RnVal - (((uint32_t)RmVal) << RsVal);
        dissassembledInstruction = QString("%1 %2, %3, %4, %5 %6").arg("sub", regNames[Rd], regNames[Rn], regNames[Rm], "LSL", regNames[Rs]);

        //qDebug() << QString::number(cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rd)));
        break;

    case AddressingMode::LSRImmediate:
        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;

        result = RnVal - (((uint32_t)RmVal) >> shift_imm);
        dissassembledInstruction = QString("%1 %2, %3, %4, #%5").arg("sub", regNames[Rd], regNames[Rn], "LSR", QString::number(shift_imm));


        break;

    case AddressingMode::LSRRegister:

        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));
        RsVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rs));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;
        if(Rs == 15) RsVal += 4;

        result =  RnVal - (((uint32_t)RmVal) >> RsVal);
        dissassembledInstruction = QString("%1 %2, %3, %4, %5 %6").arg("sub", regNames[Rd], regNames[Rn], regNames[Rm], "LSR", regNames[Rs]);


        break;

    case AddressingMode::ASRImmediate:
        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;

        result = RnVal - (RmVal >> shift_imm);
        dissassembledInstruction = QString("%1 %2, %3, %4, #%5").arg("sub", regNames[Rd], regNames[Rn], "ASR", QString::number(shift_imm));

        break;

    case AddressingMode::ASRRegister:

        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));
        RsVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rs));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;
        if(Rs == 15) RsVal += 4;

        result = RnVal - (RmVal >> RsVal);
        dissassembledInstruction = QString("%1 %2, %3, %4, %5 %6").arg("sub", regNames[Rd], regNames[Rn], regNames[Rm], "ASR", regNames[Rs]);


        break;
    case AddressingMode::RORImmediate:
        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));

        if(Rm == 15) RmVal += 4;
        if(Rn == 15) RnVal += 4;

        if(shift_imm > 0)
        {
            result = RnVal - Instruction::cpu->rotr(RmVal, shift_imm);
            dissassembledInstruction = QString("%1 %2, %3, %4, #%5").arg("sub", regNames[Rd], regNames[Rn], "ROR", QString::number(shift_imm));

        }
        break;
    case AddressingMode::RORRegister:
        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));
        RsVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rs));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;
        if(Rs == 15) RsVal += 4;

        result = RnVal - Instruction::cpu->rotr(RmVal, RsVal);
        dissassembledInstruction = QString("%1 %2, %3, %4, #%5").arg("sub", regNames[Rd], regNames[Rn], "ROR", QString::number(shift_imm));

        break;
    case AddressingMode::RORExtend:
        break;
    }
}
