#include "mov.h"
#include "dataprocessinginstruction.h"
#include "cpu.h"
#include "instruction.h"
#include <QDebug>

MOV::MOV() : DataProcessingInstruction()
{

}

void MOV::execute()
{

    switch (AddressingModeType)
    {
    case AddressingMode::Immediate:

        Instruction::cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), result);

       // dissassembledInstruction = dissassembledInstruction.arg("mov", regNames[Rd], QString::number(resultInt));
    break;

    case AddressingMode::Register:


        Instruction::cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), result);
        //dissassembledInstruction =dissassembledInstruction.arg("mov", regNames[Rd], regNames[Rn]);
        break;

    case AddressingMode::LSLImmediate:

        Instruction::cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), result);

        //dissassembledInstruction = dissassembledInstruction.arg("mov", regNames[Rd], regNames[Rm], "LSL", QString::number(resultUint));

        break;

    case AddressingMode::LSLRegister:

        Instruction::cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), result);

        //dissassembledInstruction = dissassembledInstruction.arg("mov", regNames[Rd], regNames[Rm], "LSL", regNames[Rs]);

        break;

    case AddressingMode::LSRImmediate:



        Instruction::cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), result);

        //dissassembledInstruction = dissassembledInstruction.arg("mov", regNames[Rd], regNames[Rm], "LSR", QString::number(resultUint));

        break;

    case AddressingMode::LSRRegister:



        Instruction::cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), result);
        //dissassembledInstruction = dissassembledInstruction.arg("mov", regNames[Rd], regNames[Rm], "LSR", regNames[Rs]);

        break;

    case AddressingMode::ASRImmediate:



        Instruction::cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), result);

        //dissassembledInstruction = dissassembledInstruction.arg("mov", regNames[Rd], regNames[Rm], "ASR", QString::number(resultInt));

        break;

    case AddressingMode::ASRRegister:



        Instruction::cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), (RmVal >> RsVal));
       // dissassembledInstruction = dissassembledInstruction.arg("mov", regNames[Rd], regNames[Rm], "LSR", regNames[Rs]);

        break;
    case AddressingMode::RORImmediate:


        if(shift_imm > 0)
        {

            Instruction::cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), result);
           // dissassembledInstruction = dissassembledInstruction.arg("mov", regNames[Rd], regNames[Rm], "ROR", QString::number(resultInt));
        }


        break;
    case AddressingMode::RORRegister:

        Instruction::cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), Instruction::cpu->rotr(RmVal, RsVal));
        //dissassembledInstruction = dissassembledInstruction.arg("mov", regNames[Rd], regNames[Rm], "ROR", regNames[Rs]);

        break;
    case AddressingMode::RORExtend:
        break;

    }

    if(S == 1 && Rd == 15)
    {
        //qDebug() << "Rd is r15";
        switch (cpu->mode)
        {
        case CPU_MODE::IRQ:
            cpu->regs->WriteWord(cpu->GET_REG_ADDR(CPSR), cpu->regs->ReadWord(cpu->GET_REG_ADDR(SPSR_IRQ)));
            break;
        case CPU_MODE::SVC:
            cpu->regs->WriteWord(cpu->GET_REG_ADDR(CPSR), cpu->regs->ReadWord(cpu->GET_REG_ADDR(SPSR_SVC)));
            break;
        }
        int mode = Instruction::ExtractBits(cpu->regs->ReadWord(cpu->GET_REG_ADDR(CPSR)), 0,4);

        if(mode == 0b10010)
        {
            cpu->mode = CPU_MODE::IRQ;
        }
        else if(mode == 0b10011)
        {
           cpu->mode = CPU_MODE::SVC;
        }
        else
        {
            cpu->mode = CPU_MODE::SYS;
        }
    }

    else if(S == 1)
    {
        N = ((result & N_flag_mask) >> N_bit) && 1;
        Z = result == 0 ? 1 : 0;
        C = shifter_carry_out;
        cpu->regs->SetFlag(cpu->GET_REG_ADDR(CPSR), N_bit, N);
        cpu->regs->SetFlag(cpu->GET_REG_ADDR(CPSR), Z_bit, Z);
        cpu->regs->SetFlag(cpu->GET_REG_ADDR(CPSR), C_bit, C);

    }
}

void MOV::decode()
{
    int RsVal0to7;
    DataProcessingInstruction::decode();
    switch (AddressingModeType)
    {
    case AddressingMode::Immediate:
        result = Instruction::cpu->rotr(immed_8, 2*rotate_imm);
        dissassembledInstruction = dissassembledInstruction.arg("mov", regNames[Rd], QString::number(result));

        if(rotate_imm != 0)
        {
            shifter_carry_out = Instruction::ExtractBits(result, 31,31);
        }
        else
        {
            shifter_carry_out = cpu->regs->TestFlag(cpu->GET_REG_ADDR(CPSR), C);
        }

        break;

    case AddressingMode::Register:
        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;

        result = RmVal;

        shifter_carry_out = cpu->regs->TestFlag(cpu->GET_REG_ADDR(CPSR), C);

        dissassembledInstruction = dissassembledInstruction.arg("mov", regNames[Rd], regNames[Rm]);
        break;

    case AddressingMode::LSLImmediate:
        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;
        result = (((uint32_t)RmVal) << shift_imm);

        if(shift_imm == 0)
        {
            shifter_carry_out = cpu->regs->TestFlag(cpu->GET_REG_ADDR(CPSR), C);
        }
        else
        {
            shifter_carry_out = Instruction::ExtractBits(RmVal, 32 - shift_imm, 32 - shift_imm);
        }
        dissassembledInstruction = dissassembledInstruction.arg("mov", regNames[Rd], regNames[Rm], "lsl", QString::number(shift_imm));

        break;

    case AddressingMode::LSLRegister:
        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));
        RsVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rs));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;
        if(Rs == 15) RsVal += 4;

        result = (((uint32_t)RmVal) << RsVal);

        RsVal0to7 = Instruction::ExtractBits(RsVal, 0, 7);

        if(RsVal0to7 == 0)
        {
            shifter_carry_out = cpu->regs->TestFlag(cpu->GET_REG_ADDR(CPSR), C);
        }
        else if(RsVal0to7 < 32)
        {
            shifter_carry_out = Instruction::ExtractBits(RmVal, 32 - RsVal0to7, 32 - RsVal0to7);
        }
        else if(RsVal0to7 == 32)
        {
            shifter_carry_out = Instruction::ExtractBits(RmVal, 0,0);
        }
        else
        {
            shifter_carry_out = 0;
        }

        dissassembledInstruction = dissassembledInstruction.arg("mov", regNames[Rd], regNames[Rm], "lsl", regNames[Rs]);

        break;

    case AddressingMode::LSRImmediate:
        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;

        result = (((uint32_t)RmVal) >> shift_imm);

        if(shift_imm == 0)
        {
            shifter_carry_out = Instruction::ExtractBits(RmVal, 31, 31);
        }
        else
        {
            shifter_carry_out = Instruction::ExtractBits(RmVal, shift_imm-1, shift_imm-1);
        }

        dissassembledInstruction = dissassembledInstruction.arg("mov", regNames[Rd], regNames[Rm], "lsr", QString::number(shift_imm));

        break;

    case AddressingMode::LSRRegister:

        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));
        RsVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rs));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;
        if(Rs == 15) RsVal += 4;

        result = (((uint32_t)RmVal) >> RsVal);

        RsVal0to7 = Instruction::ExtractBits(RsVal, 0, 7);

        if(RsVal0to7 == 0)
        {
            shifter_carry_out = cpu->regs->TestFlag(cpu->GET_REG_ADDR(CPSR), C);
        }
        else if(RsVal0to7 < 32)
        {
            shifter_carry_out = Instruction::ExtractBits(RmVal, RsVal0to7 - 1, RsVal0to7 - 1);
        }
        else if(RsVal0to7 == 32)
        {
            shifter_carry_out = Instruction::ExtractBits(RmVal, 31,31);
        }
        else
        {
            shifter_carry_out = 0;
        }


        dissassembledInstruction = dissassembledInstruction.arg("mov", regNames[Rd], regNames[Rm], "lsr", regNames[Rs]);

        break;

    case AddressingMode::ASRImmediate:
        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;

        result = (RmVal >> shift_imm);

        if(shift_imm == 0)
        {
            shifter_carry_out = Instruction::ExtractBits(RmVal, 31,31);
        }
        else
        {
            shifter_carry_out = Instruction::ExtractBits(RmVal, shift_imm -1 , shift_imm - 1);
        }

        dissassembledInstruction = dissassembledInstruction.arg("mov", regNames[Rd], regNames[Rm], "asr", QString::number(shift_imm));

        break;

    case AddressingMode::ASRRegister:

        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));
        RsVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rs));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;
        if(Rs == 15) RsVal += 4;

        result = (RmVal >> RsVal);

        if(RsVal0to7 == 0)
        {
            shifter_carry_out = cpu->regs->TestFlag(cpu->GET_REG_ADDR(CPSR), C);
        }
        else if(RsVal0to7 < 32)
        {
            shifter_carry_out = Instruction::ExtractBits(RmVal, RsVal0to7 - 1, RsVal0to7 - 1);
        }
        else
        {
            shifter_carry_out = Instruction::ExtractBits(RmVal, 31,31);
        }



        dissassembledInstruction = dissassembledInstruction.arg("mov", regNames[Rd], regNames[Rm], "lsr", regNames[Rs]);

        break;
    case AddressingMode::RORImmediate:
        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));

        if(Rm == 15) RmVal += 4;
        if(Rn == 15) RnVal += 4;

        if(shift_imm > 0)
        {
            result = Instruction::cpu->rotr(RmVal, shift_imm);

            shifter_carry_out = Instruction::ExtractBits(RmVal, shift_imm -1, shift_imm -1);
            dissassembledInstruction = dissassembledInstruction.arg("mov", regNames[Rd], regNames[Rm], "ror", QString::number(shift_imm));
        }



        break;
    case AddressingMode::RORRegister:
        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));
        RsVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rs));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;
        if(Rs == 15) RsVal += 4;

        result = Instruction::cpu->rotr(RmVal, RsVal);

        if(Instruction::ExtractBits(RsVal, 0, 7) == 0)
        {
            shifter_carry_out = cpu->regs->TestFlag(cpu->GET_REG_ADDR(CPSR), C);
        }
        else if(Instruction::ExtractBits(RsVal, 0, 4) == 0)
        {
            shifter_carry_out = Instruction::ExtractBits(RmVal, 31, 31);
        }
        else
        {
            shifter_carry_out = Instruction::ExtractBits(RmVal, Instruction::ExtractBits(RsVal, 0, 4) - 1, Instruction::ExtractBits(RsVal, 0, 4) - 1);
        }
        dissassembledInstruction = dissassembledInstruction.arg("mov", regNames[Rd], regNames[Rm], "ror", regNames[Rs]);

        break;
    }


}
