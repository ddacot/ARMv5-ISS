#include "cmp.h"
#include <QDebug>
CMP::CMP(): DataProcessingInstruction ()
{

}

void CMP::decode()
{
    Instruction::decode();
    DataProcessingInstruction::decode();

    switch (AddressingModeType)
    {
    case AddressingMode::Immediate:

        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));

        if(Rn == 15) RnVal += 4;
        operand2 = Instruction::cpu->rotr(immed_8, 2*rotate_imm);
        result = RnVal - operand2;

        dissassembledInstruction = QString("%1 %2,#%3").arg("cmp", regNames[Rn], QString::number(Instruction::cpu->rotr(immed_8, 2*rotate_imm)));

    break;

    case AddressingMode::Register:
        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;

        operand2 = RmVal;
        result = RnVal - operand2;

        dissassembledInstruction = QString("%1 %2, %3, #%3").arg("cmp", regNames[Rn], regNames[Rm]);

        break;

    case AddressingMode::LSLImmediate:
        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;

        operand2 = (((uint32_t)RmVal) << shift_imm);
        result = RnVal - operand2;

        dissassembledInstruction = QString("%1 %2, %3, #%4").arg("cmp", regNames[Rn], "LSL", QString::number(shift_imm));

        break;

    case AddressingMode::LSLRegister:
        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));
        RsVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rs));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;
        if(Rs == 15) RsVal += 4;

        operand2 = (((uint32_t)RmVal) << RsVal);
        result = RnVal - operand2;
        dissassembledInstruction = QString("%1 %2, %3, %4, %5").arg("cmp", regNames[Rn], regNames[Rm], "LSL", regNames[Rs]);

        break;

    case AddressingMode::LSRImmediate:
        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;

        operand2 = (((uint32_t)RmVal) >> shift_imm);
        result = RnVal - operand2;

        dissassembledInstruction = QString("%1 %2, %3, #%4").arg("cmp", regNames[Rn], "LSR", QString::number(shift_imm));

        break;

    case AddressingMode::LSRRegister:

        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));
        RsVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rs));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;
        if(Rs == 15) RsVal += 4;

        operand2 = (((uint32_t)RmVal) >> RsVal);
        result = RnVal - operand2;
        dissassembledInstruction = QString("%1 %2, %3, %4, %5").arg("cmp", regNames[Rn], regNames[Rm], "LSR", regNames[Rs]);

        break;

    case AddressingMode::ASRImmediate:
        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;

        operand2 = (RmVal >> shift_imm);
        result = RnVal - operand2;
        dissassembledInstruction = QString("%1 %2, %3, #%4").arg("cmp",regNames[Rn], "ASR", QString::number(shift_imm));

        break;

    case AddressingMode::ASRRegister:

        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));
        RsVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rs));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;
        if(Rs == 15) RsVal += 4;
        operand2 = (RmVal >> RsVal);
        result = RnVal - operand2 ;
        dissassembledInstruction = QString("%1 %2, %3, %4, %5").arg("cmp", regNames[Rn], regNames[Rm], "ASR", regNames[Rs]);


        break;
    case AddressingMode::RORImmediate:
        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));

        if(Rm == 15) RmVal += 4;
        if(Rn == 15) RnVal += 4;

        if(shift_imm > 0)
        {
            operand2 = Instruction::cpu->rotr(RmVal, shift_imm);
            result = RnVal - operand2;
            dissassembledInstruction = QString("%1 %2, %3, #%4").arg("cmp", regNames[Rn], "ROR", QString::number(shift_imm));
        }
        break;
    case AddressingMode::RORRegister:
        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));
        RsVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rs));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;
        if(Rs == 15) RsVal += 4;

        operand2 = Instruction::cpu->rotr(RmVal, RsVal);
        result = RnVal - operand2;

        dissassembledInstruction = QString("%1 %2, %3, %4, %5").arg("cmp", regNames[Rn], regNames[Rm], "ROR", regNames[Rs]);

        break;
    case AddressingMode::RORExtend:
        break;

    }
}

void CMP::execute()
{
    bool N,Z,C,V;

    N = ((result & N_flag_mask) >> N_bit) && 1;
    Z = result == 0 ? 1 : 0;

    if((uint32_t)operand2 <= (uint32_t)RnVal)
    {
        C = 1;
    }
    else
    {
        C = 0;
    }

    if(((RnVal & 0x80000000) != (operand2 & 0x80000000)) && ((RnVal & 0x80000000) != (result & 0x80000000)))
    {
        V = 1;
    }
    else
    {
        V = 0;
    }
    //msb op1 != msb op2 && msbop1 != msb res

    cpu->regs->SetFlag(cpu->GET_REG_ADDR(CPSR), N_bit, N);
    cpu->regs->SetFlag(cpu->GET_REG_ADDR(CPSR), Z_bit, Z);
    cpu->regs->SetFlag(cpu->GET_REG_ADDR(CPSR), C_bit, C);
    cpu->regs->SetFlag(cpu->GET_REG_ADDR(CPSR), V_bit, V);

}
