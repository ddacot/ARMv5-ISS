#include "ldr.h"
#include <QDebug>
LDR::LDR(): LoadStoreInstruction ()
{

}

void LDR::decode()
{
    Instruction::decode();
    LoadStoreInstruction::decode();


    RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
    RdVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rd));

    switch (AddressingModeType)
    {
    case AddressingMode::Immediate:

        //qDebug() << Rd << RnVal << offset_12;
        if(Rn == 15) RnVal += 4;

        if(U == 1)
        {
            //qDebug() << RnVal << offset_12;
            address = RnVal + offset_12;

        }
        else
        {
            address = RnVal - offset_12;
        }

        dissassembledInstruction = dissassembledInstruction.arg(B==1 ? "ldrb" : "ldr", regNames[Rd], regNames[Rn], QString::number(U==1 ? offset_12 : -offset_12));


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

        dissassembledInstruction = dissassembledInstruction.arg(B==1 ? "ldrb" : "ldr", regNames[Rd], regNames[Rn], (U==1 ? regNames[Rm] : ("-" + regNames[Rm])));

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
            dissassembledInstruction = dissassembledInstruction.arg(B==1 ? "ldrb" : "ldr", regNames[Rd], regNames[Rn], (U==1 ? regNames[Rm] : ("-" + regNames[Rm])), "lsl", QString::number(shift_imm));

        break;
        case 1:
            //lsr
            RmVal = (uint32_t)RmVal >> shift_imm;
            dissassembledInstruction = dissassembledInstruction.arg(B==1 ? "ldrb" : "ldr", regNames[Rd], regNames[Rn], (U==1 ? regNames[Rm] : ("-" + regNames[Rm])), "lsr", QString::number(shift_imm));

            break;
        case 2:
            //asr
            RmVal >>= shift_imm;
            dissassembledInstruction = dissassembledInstruction.arg(B==1 ? "ldrb" : "ldr", regNames[Rd], regNames[Rn], (U==1 ? regNames[Rm] : ("-" + regNames[Rm])), "asr", QString::number(shift_imm));

            break;
        case 3:
            RmVal = Instruction::cpu->rotr(RmVal, shift_imm);
            dissassembledInstruction = dissassembledInstruction.arg(B==1 ? "ldrb" : "ldr", regNames[Rd], regNames[Rn], (U==1 ? regNames[Rm] : ("-" + regNames[Rm])), "ror", QString::number(shift_imm));

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
        dissassembledInstruction = dissassembledInstruction.arg(B==1 ? "ldrb" : "ldr", regNames[Rd], regNames[Rn], QString::number(U==1 ? offset_12 : -offset_12));

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

        dissassembledInstruction = dissassembledInstruction.arg(B==1 ? "ldrb" : "ldr", regNames[Rd], regNames[Rn], (U==1 ? regNames[Rm] : ("-" + regNames[Rm])));


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
            dissassembledInstruction = dissassembledInstruction.arg(B==1 ? "ldrb" : "ldr", regNames[Rd], regNames[Rn], (U==1 ? regNames[Rm] : ("-" + regNames[Rm])), "lsl", QString::number(shift_imm));

            break;
        case 1:
            //lsr
            RmVal = (uint32_t)RmVal >> shift_imm;
            dissassembledInstruction = dissassembledInstruction.arg(B==1 ? "ldrb" : "ldr", regNames[Rd], regNames[Rn], (U==1 ? regNames[Rm] : ("-" + regNames[Rm])), "lsr", QString::number(shift_imm));

            break;
        case 2:
            //asr
            RmVal >>= shift_imm;
            dissassembledInstruction = dissassembledInstruction.arg(B==1 ? "ldrb" : "ldr", regNames[Rd], regNames[Rn], (U==1 ? regNames[Rm] : ("-" + regNames[Rm])), "asr", QString::number(shift_imm));

            break;
        case 3:
            RmVal = Instruction::cpu->rotr(RmVal, shift_imm);
            dissassembledInstruction = dissassembledInstruction.arg(B==1 ? "ldrb" : "ldr", regNames[Rd], regNames[Rn], (U==1 ? regNames[Rm] : ("-" + regNames[Rm])), "ror", QString::number(shift_imm));

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
void LDR::execute()
{

    switch (AddressingModeType)
    {
    case AddressingMode::Immediate:
        if(B == 0)
        {
            cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), (uint32_t)cpu->ram->ReadWord(address));
        }
        else
        {
            cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), cpu->ram->ReadByte(address));
        }

    break;

    case AddressingMode::Register:

        if(B == 0)
        {
            cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), cpu->ram->ReadWord(address));
        }
        else
        {
            cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), cpu->ram->ReadByte(address));
        }

        break;


    case AddressingMode::ScaledRegister:
        if(B == 0)
        {
            cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), cpu->ram->ReadWord(address));
        }
        else
        {
            cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), cpu->ram->ReadByte(address));
        }
        break;

    case AddressingMode::ImmediatePreIndexed:
        if(B == 0)
        {
            cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), cpu->ram->ReadByte(address));
        }
        else
        {
            cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), cpu->ram->ReadWord(address));
        }

        cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rn), address);

        break;

    case AddressingMode::RegisterPreIndexed:

        if(B == 0)
        {
            cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), cpu->ram->ReadWord(address));
        }
        else
        {
            cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), cpu->ram->ReadByte(address));
        }

        cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rn), address);

        break;
    case AddressingMode::ScaledRegisterPreIndexed:


        if(B == 0)
        {
            cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), cpu->ram->ReadWord(address));
        }
        else
        {
            cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), cpu->ram->ReadByte(address));
        }

        cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rn), address);
        break;
    }

}
