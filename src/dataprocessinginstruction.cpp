#include "dataprocessinginstruction.h"
#include "cpu.h"
#include <QtDebug>
DataProcessingInstruction::DataProcessingInstruction() : Instruction()
{

}

void DataProcessingInstruction::decode()
{
    condition = Instruction::ExtractBits(assembledInstruction, 28, 31);
    S = Instruction::ExtractBits(assembledInstruction, 20, 20);
    I = Instruction::ExtractBits(this->assembledInstruction, 25, 25);

    if(I == 1)
    {
        this->AddressingModeType = AddressingMode::Immediate;
    }
    else if(I == 0)
    {
        //case where instruciton is a MUL instruction, it has only register type.
        if(Instruction::ExtractBits(this->assembledInstruction, 4, 11) == 0 || Instruction::ExtractBits(this->assembledInstruction, 4, 7) == 9)
        {
            this->AddressingModeType = AddressingMode::Register;
        }
        else if(Instruction::ExtractBits(this->assembledInstruction, 4,6) == 0)
        {
            this->AddressingModeType = AddressingMode::LSLImmediate;
        }
        else if(Instruction::ExtractBits(this->assembledInstruction, 4,7) == 1)
        {
            this->AddressingModeType = AddressingMode::LSLRegister;
        }
        else if(Instruction::ExtractBits(this->assembledInstruction, 4,6) == 2)
        {
            this->AddressingModeType = AddressingMode::LSRImmediate;
        }
        else if(Instruction::ExtractBits(this->assembledInstruction, 4,6) == 3)
        {
            this->AddressingModeType = AddressingMode::LSRRegister;
        }
        else if(Instruction::ExtractBits(this->assembledInstruction, 4,6) == 4)
        {
            this->AddressingModeType = AddressingMode::ASRImmediate;
        }
        else if(Instruction::ExtractBits(this->assembledInstruction, 4,7) == 5)
        {
            this->AddressingModeType = AddressingMode::ASRRegister;
        }
        else if(Instruction::ExtractBits(this->assembledInstruction, 4,6) == 6)
        {
            this->AddressingModeType = AddressingMode::RORImmediate;
        }
        else if(Instruction::ExtractBits(this->assembledInstruction, 4,7) == 7)
        {
            this->AddressingModeType = AddressingMode::RORRegister;
        }
    }

    //this->operands = new AddressingMode();


    this->opcode = Instruction::ExtractBits(assembledInstruction, 21, 24);
    this->S = Instruction::ExtractBits(assembledInstruction, 20, 20);
    this->Rn = Instruction::ExtractBits(assembledInstruction, 16, 19);
    this->Rd = Instruction::ExtractBits(assembledInstruction, 12, 15);

    switch (this->AddressingModeType) {
    case AddressingMode::Immediate:
        dissassembledInstruction = "%1 %2, #%3";
        this->rotate_imm = Instruction::ExtractBits(assembledInstruction, 8, 11);
        this->immed_8 = Instruction::ExtractBits(assembledInstruction, 0, 7);
        break;

    case AddressingMode::Register:
        dissassembledInstruction = "%1 %2, %3";
        this->Rm = Instruction::ExtractBits(assembledInstruction, 0, 3);
        this->Rs = Instruction::ExtractBits(assembledInstruction, 8,11);
        break;

    case AddressingMode::LSLImmediate:
    case AddressingMode::LSRImmediate:
    case AddressingMode::ASRImmediate:
    case AddressingMode::RORImmediate:
        dissassembledInstruction = "%1 %2, %3, %4 #%5";
        this->shift_imm = Instruction::ExtractBits(assembledInstruction, 7, 11);
        this->Rm = Instruction::ExtractBits(assembledInstruction, 0, 3);
        break;

    case AddressingMode::LSLRegister:
    case AddressingMode::LSRRegister:
    case AddressingMode::ASRRegister:
    case AddressingMode::RORRegister:
        dissassembledInstruction = "%1 %2, %3, %4, %5, %6";
        this->Rs = Instruction::ExtractBits(assembledInstruction, 8, 11);
        this->Rm = Instruction::ExtractBits(assembledInstruction, 0, 3);
        break;

    case AddressingMode::RORExtend:

        this->Rm = Instruction::ExtractBits(assembledInstruction, 0, 3);
        break;

    }

    if(shift_imm == 0)
    {
        shift_imm = 32;
    }
}

void DataProcessingInstruction::execute()
{

}
