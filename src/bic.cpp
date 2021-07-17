#include "bic.h"

BIC::BIC(): DataProcessingInstruction ()
{

}

void BIC::decode()
{
    Instruction::decode();
    DataProcessingInstruction::decode();

    int RnVal, RmVal, RsVal;

    RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
    RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));
    RsVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rs));

    if(Rn == 15) RnVal += 4;
    if(Rm == 15) RmVal += 4;
    if(Rs == 15) RsVal += 4;

    switch (AddressingModeType)
    {
    case AddressingMode::Immediate:
       // RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));

        //if(Rn == 15) RnVal += 4;

        result= RnVal & ~Instruction::cpu->rotr(immed_8, 2*rotate_imm);
        dissassembledInstruction = QString("%1 %2,%3,#%4").arg("bic", regNames[Rd], regNames[Rn], QString::number(Instruction::cpu->rotr(immed_8, 2*rotate_imm)));

    break;

    case AddressingMode::Register:

        result = RnVal & ~RmVal;
        dissassembledInstruction = QString("%1 %2, %3, %3, %4").arg("bic", regNames[Rd], regNames[Rn], regNames[Rm]);

        break;

    case AddressingMode::LSLImmediate:


        result = RnVal & ~(((uint32_t)RmVal) << shift_imm);
        dissassembledInstruction = QString("%1 %2, %3, %4, #%5").arg("bic", regNames[Rd], regNames[Rn], "LSL", QString::number(shift_imm));

        break;

    case AddressingMode::LSLRegister:


        result = RnVal & ~(((uint32_t)RmVal) << RsVal);
        dissassembledInstruction = QString("%1 %2, %3, %4, %5 %6").arg("bic", regNames[Rd], regNames[Rn], regNames[Rm], "LSL", regNames[Rs]);

        break;

    case AddressingMode::LSRImmediate:


        result = RnVal & ~(((uint32_t)RmVal) >> shift_imm);
        dissassembledInstruction = QString("%1 %2, %3, %4, #%5").arg("bic", regNames[Rd], regNames[Rn], "LSR", QString::number(shift_imm));

        break;

    case AddressingMode::LSRRegister:



        result = RnVal & ~(((uint32_t)RmVal) >> RsVal);
        dissassembledInstruction = QString("%1 %2, %3, %4, %5 %6").arg("bic", regNames[Rd], regNames[Rn], regNames[Rm], "LSR", regNames[Rs]);

        break;

    case AddressingMode::ASRImmediate:

        result = RnVal & ~(RmVal >> shift_imm);
        dissassembledInstruction = QString("%1 %2, %3, %4, #%5").arg("bic", regNames[Rd], regNames[Rn], "ASR", QString::number(shift_imm));

        break;

    case AddressingMode::ASRRegister:


        result = RnVal & ~(RmVal >> RsVal);
        dissassembledInstruction = QString("%1 %2, %3, %4, %5 %6").arg("bic", regNames[Rd], regNames[Rn], regNames[Rm], "ASR", regNames[Rs]);

        break;
    case AddressingMode::RORImmediate:


        if(shift_imm > 0)
        {
            result = RnVal & ~Instruction::cpu->rotr(RmVal, shift_imm);
            dissassembledInstruction = QString("%1 %2, %3, %4, #%5").arg("bic", regNames[Rd], regNames[Rn], "ROR", QString::number(shift_imm));

        }
        break;
    case AddressingMode::RORRegister:

        result = RnVal & ~Instruction::cpu->rotr(RmVal, RsVal);
        dissassembledInstruction = QString("%1 %2, %3, %4, %5 %6").arg("bic", regNames[Rd], regNames[Rn], regNames[Rm], "ROR", regNames[Rs]);

        break;


    }
}

void BIC::execute()
{

    switch (AddressingModeType)
    {
    case AddressingMode::Immediate:

        Instruction::cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), result);

        break;

    case AddressingMode::Register:

        Instruction::cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), result);

        break;

    case AddressingMode::LSLImmediate:

        Instruction::cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), result);

        break;

    case AddressingMode::LSLRegister:

        Instruction::cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), result);

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

        Instruction::cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd),result);

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
