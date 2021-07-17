#include "str.h"
#include <QtDebug>
STR::STR(): LoadStoreInstruction()
{

}

void STR::decode()
{
    LoadStoreInstruction::decode();

    RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
    RdVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rd));

    switch (AddressingModeType)
    {
    case AddressingMode::Immediate:

        if(Rn == 15) RnVal += 4;
        if(Rd == 15) RdVal += 4;


        if(U == 1)
        {
            address = RnVal + offset_12;
        }
        else
        {
            //qDebug() << this->assembledInstruction;
            address = RnVal - offset_12;
            //qDebug() << RnVal << offset_12;

        }
        dissassembledInstruction = dissassembledInstruction.arg(B==1 ? "strb" : "str", regNames[Rd], regNames[Rn], QString::number(U==1 ? offset_12 : -offset_12));
    break;

    case AddressingMode::Register:
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;

        if(U == 1)
        {
            address = RnVal + RmVal;
        }
        else
        {
            address = RnVal - RmVal;
        }
        dissassembledInstruction = dissassembledInstruction.arg(B==1 ? "strb" : "str", regNames[Rd], regNames[Rn], (U==1 ? regNames[Rm] : ("-" + regNames[Rm])));
        break;


    case AddressingMode::ScaledRegister:

        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;

        switch (shift)
        {
        case 0:
            //lsl
            RmVal = (uint32_t)RmVal << shift_imm;
            dissassembledInstruction = dissassembledInstruction.arg(B==1 ? "strb" : "str", regNames[Rd], regNames[Rn], (U==1 ? regNames[Rm] : ("-" + regNames[Rm])), "lsl", QString::number(shift_imm));

        break;
        case 1:
            //lsr
            RmVal = (uint32_t)RmVal >> shift_imm;
            dissassembledInstruction = dissassembledInstruction.arg(B==1 ? "strb" : "str", regNames[Rd], regNames[Rn], (U==1 ? regNames[Rm] : ("-" + regNames[Rm])), "lsr", QString::number(shift_imm));
            break;
        case 2:
            //asr
            RmVal >>= shift_imm;
            dissassembledInstruction = dissassembledInstruction.arg(B==1 ? "strb" : "str", regNames[Rd], regNames[Rn], (U==1 ? regNames[Rm] : ("-" + regNames[Rm])), "asr", QString::number(shift_imm));
            break;
        case 3:
            RmVal = Instruction::cpu->rotr(RmVal, shift_imm);
            dissassembledInstruction = dissassembledInstruction.arg(B==1 ? "strb" : "str", regNames[Rd], regNames[Rn], (U==1 ? regNames[Rm] : ("-" + regNames[Rm])), "ror", QString::number(shift_imm));
            //ror
            break;
        }

        if(U == 1)
        {
            address = RnVal + RmVal;
        }
        else
        {
            address = RnVal - RmVal;
        }

        break;
    case AddressingMode::ImmediatePreIndexed:
        if(Rn == 15) RnVal += 4;

        if(U == 1)
        {
            address = RnVal + offset_12;
        }
        else
        {
            address = RnVal - offset_12;
        }
        dissassembledInstruction = dissassembledInstruction.arg(B==1 ? "strb" : "str", regNames[Rd], regNames[Rn], QString::number(U==1 ? offset_12 : -offset_12));

        break;
    case AddressingMode::RegisterPreIndexed:
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;

        if(U == 1)
        {
            address = RnVal + RmVal;
        }
        else
        {
            address = RnVal - RmVal;
        }

        dissassembledInstruction = dissassembledInstruction.arg(B==1 ? "strb" : "str", regNames[Rd], regNames[Rn], (U==1 ? regNames[Rm] : ("-" + regNames[Rm])));

        break;
    case AddressingMode::ScaledRegisterPreIndexed:
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;

        switch (shift)
        {
        case 0:
            //lsl
            RmVal = (uint32_t)RmVal << shift_imm;
            dissassembledInstruction = dissassembledInstruction.arg(B==1 ? "strb" : "str", regNames[Rd], regNames[Rn], (U==1 ? regNames[Rm] : ("-" + regNames[Rm])), "lsl", QString::number(shift_imm));

        break;
        case 1:
            //lsr
            RmVal = (uint32_t)RmVal >> shift_imm;
            dissassembledInstruction = dissassembledInstruction.arg(B==1 ? "strb" : "str", regNames[Rd], regNames[Rn], (U==1 ? regNames[Rm] : ("-" + regNames[Rm])), "lsr", QString::number(shift_imm));

            break;
        case 2:
            //asr
            RmVal >>= shift_imm;
            dissassembledInstruction = dissassembledInstruction.arg(B==1 ? "strb" : "str", regNames[Rd], regNames[Rn], (U==1 ? regNames[Rm] : ("-" + regNames[Rm])), "asr", QString::number(shift_imm));

            break;
        case 3:
            RmVal = Instruction::cpu->rotr(RmVal, shift_imm);
            dissassembledInstruction = dissassembledInstruction.arg(B==1 ? "strb" : "str", regNames[Rd], regNames[Rn], (U==1 ? regNames[Rm] : ("-" + regNames[Rm])), "ror", QString::number(shift_imm));

            //ror
            break;
        }

        if(U == 1)
        {
            address = RnVal + RmVal;
        }
        else
        {
            address = RnVal - RmVal;
        }

        break;
    }

}
void STR::execute()
{
    switch (AddressingModeType)
    {
    case AddressingMode::Immediate:

        if(B == 0)
        {
            //qDebug() << address << RdVal;
            cpu->ram->WriteWord(address, RdVal);
        }
        else
        {
            cpu->ram->WriteByte(address, (RdVal & 0xFF));
        }

    break;

    case AddressingMode::Register:

        if(B == 0)
        {
            cpu->ram->WriteWord(address, RdVal);
        }
        else
        {
            cpu->ram->WriteByte(address, (RdVal & 0xFF));
        }

        break;


    case AddressingMode::ScaledRegister:


        if(B == 0)
        {
            cpu->ram->WriteWord(address, RdVal);
        }
        else
        {
            cpu->ram->WriteByte(address,  (uint8_t)(RdVal & 0xFF));
        }

        break;
    case AddressingMode::ImmediatePreIndexed:

        if(B == 0)
        {
            cpu->ram->WriteWord(address, RdVal);
        }
        else
        {
            cpu->ram->WriteByte(address,  (uint8_t)(RdVal & 0xFF));
        }

        cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rn), address);

        break;
    case AddressingMode::RegisterPreIndexed:

        if(B == 0)
        {
            cpu->ram->WriteWord(address, RdVal);
        }
        else
        {
            cpu->ram->WriteByte(address,  (uint8_t)(RdVal & 0xFF));
        }

        cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rn), address);

        break;
    case AddressingMode::ScaledRegisterPreIndexed:

        if(B == 0)
        {
            cpu->ram->WriteWord(address, RdVal);
        }
        else
        {
            cpu->ram->WriteByte(address, (uint8_t)(RdVal & 0xFF));
        }

        cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rn), address);
        break;
    }

}
