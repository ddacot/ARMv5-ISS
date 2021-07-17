#include "mvn.h"
#include "instruction.h"

MVN::MVN() : DataProcessingInstruction()
{

}
void MVN::execute()
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

        Instruction::cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), result);

        break;
    case AddressingMode::RORImmediate:

        if(shift_imm > 0)
        {
            Instruction::cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd), result);
        }
        break;
    case AddressingMode::RORRegister:


        Instruction::cpu->regs->WriteWord(Instruction::cpu->GET_REG_ADDR(Rd),result);
        break;


    }
}

void MVN::decode()
{
    DataProcessingInstruction::decode();

    switch (AddressingModeType)
    {
    case AddressingMode::Immediate:
        result = ~(Instruction::cpu->rotr(immed_8, 2*rotate_imm));
        dissassembledInstruction = dissassembledInstruction.arg("mvn", regNames[Rd], QString::number((Instruction::cpu->rotr(immed_8, 2*rotate_imm))));

    break;

    case AddressingMode::Register:
        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;

        result = ~RmVal;

        dissassembledInstruction = dissassembledInstruction.arg("mvn", regNames[Rd], regNames[Rm]);

        break;

    case AddressingMode::LSLImmediate:
        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;

        result =  ~(((uint32_t)RmVal) << shift_imm);
        dissassembledInstruction = dissassembledInstruction.arg("mvn", regNames[Rd], regNames[Rm], "lsl", QString::number(shift_imm));

        break;

    case AddressingMode::LSLRegister:
        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));
        RsVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rs));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;
        if(Rs == 15) RsVal += 4;

        result = ~(((uint32_t)RmVal) << RsVal);
        dissassembledInstruction = dissassembledInstruction.arg("mvn", regNames[Rd], regNames[Rm], "lsl", regNames[Rs]);

        break;

    case AddressingMode::LSRImmediate:
        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;

        result = ~(((uint32_t)RmVal) >> shift_imm);
        dissassembledInstruction = dissassembledInstruction.arg("mvn", regNames[Rd], regNames[Rm], "lsr", QString::number(shift_imm));

        break;

    case AddressingMode::LSRRegister:

        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));
        RsVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rs));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;
        if(Rs == 15) RsVal += 4;

        result = ~(((uint32_t)RmVal) >> RsVal);
        dissassembledInstruction = dissassembledInstruction.arg("mvn", regNames[Rd], regNames[Rm], "lsr", regNames[Rs]);

        break;

    case AddressingMode::ASRImmediate:
        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;

        result = ~(RmVal >> shift_imm);
        dissassembledInstruction = dissassembledInstruction.arg("mvn", regNames[Rd], regNames[Rm], "asr", QString::number(shift_imm));

        break;

    case AddressingMode::ASRRegister:

        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));
        RsVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rs));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;
        if(Rs == 15) RsVal += 4;

        result = ~(RmVal >> RsVal);
        dissassembledInstruction = dissassembledInstruction.arg("mvn", regNames[Rd], regNames[Rm], "lsr", regNames[Rs]);


        break;
    case AddressingMode::RORImmediate:
        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));

        if(Rm == 15) RmVal += 4;
        if(Rn == 15) RnVal += 4;

        if(shift_imm > 0)
        {
            result = ~Instruction::cpu->rotr(RmVal, shift_imm);
            dissassembledInstruction = dissassembledInstruction.arg("mvn", regNames[Rd], regNames[Rm], "ror", QString::number(shift_imm));

        }
        break;
    case AddressingMode::RORRegister:
        RnVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rn));
        RmVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rm));
        RsVal = cpu->regs->ReadWord(Instruction::cpu->GET_REG_ADDR(Rs));

        if(Rn == 15) RnVal += 4;
        if(Rm == 15) RmVal += 4;
        if(Rs == 15) RsVal += 4;

        result = ~Instruction::cpu->rotr(RmVal, RsVal);
        dissassembledInstruction = dissassembledInstruction.arg("mvn", regNames[Rd], regNames[Rm], "ror", regNames[Rs]);

        break;
    case AddressingMode::RORExtend:
        break;

    }
}
