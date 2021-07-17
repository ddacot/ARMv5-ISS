#include "loadstoreinstruction.h"
#include <QDebug>
LoadStoreInstruction::LoadStoreInstruction()
{

}

void LoadStoreInstruction::execute()
{
    //perform a load or store based on the L value.
    //this function is overriden by each type of LOAD/STORE instruction, therefore the implementation
    //depends on actual instruction.
}

void LoadStoreInstruction::decode()
{
    this->condition = Instruction::ExtractBits(assembledInstruction, 28, 31);
    Rn = Instruction::ExtractBits(assembledInstruction, 16, 19);
    Rd = Instruction::ExtractBits(assembledInstruction, 12, 15);
    I = Instruction::ExtractBits(this->assembledInstruction, 25, 25);
    P = Instruction::ExtractBits(assembledInstruction, 24, 24);
    U = Instruction::ExtractBits(assembledInstruction, 23, 23);
    B = Instruction::ExtractBits(assembledInstruction, 22, 22);
    W = Instruction::ExtractBits(assembledInstruction, 21, 21);
    L = Instruction::ExtractBits(assembledInstruction, 20, 20);
    int bits26to27 = Instruction::ExtractBits(assembledInstruction, 26, 27);
    int bits4to11 = Instruction::ExtractBits(assembledInstruction, 4, 11);
    int bit4 = Instruction::ExtractBits(assembledInstruction, 4, 4);
    offset_12 = Instruction::ExtractBits(assembledInstruction, 0, 11);
    opcode = Instruction::ExtractBits(assembledInstruction, 25, 27);

    if((I == 0 && P == 1 && U == 0 && L == 0 && opcode == 4 ) || (I == 0 && P == 0 && U == 1 && L == 1 && opcode == 4))
    {
        this->AddressingModeType = AddressingMode::StackFullDescending;
    }
    else if(I == 0 && P == 1 && W == 0)
    {
        //immediate offset
        dissassembledInstruction = "%1 %2, [%3, #%4]";
        this->AddressingModeType = AddressingMode::Immediate;
    }
    else if(I == 1 && P == 1 && W == 0 && bits4to11 == 0)
    {
        // register offset
        dissassembledInstruction = "%1 %2, [%3, %4]";
        this->AddressingModeType = AddressingMode::Register;
        //qDebug() << "reg offset";
    }
    else if(I == 1 && P == 1 && W == 0 && bit4 == 0)
    {
        // scaled register
        dissassembledInstruction = "%1 %2, [%3, %4, %5 #%6]";
        this->AddressingModeType = AddressingMode::ScaledRegister;
    }
    else if(I == 0 && P == 1 && W == 1)
    {

        //immediate pre-indexed
        dissassembledInstruction = "%1 %2, [%3, #%4]!";
        this->AddressingModeType = AddressingMode::ImmediatePreIndexed;
    }
    else if(I == 1 && P == 1 && W == 1 && bits4to11 == 0)
    {
        //register preindexed
        dissassembledInstruction = "%1 %2, [%3, %4]!";
        this->AddressingModeType = AddressingMode::RegisterPreIndexed;
    }
    else if(I == 1 && P == 1 && W == 1 && bit4 == 0)
    {
        //scaled register preindexed
        dissassembledInstruction = "%1 %2, [%3, %4, %5 #%6]!";
        this->AddressingModeType = AddressingMode::ScaledRegisterPreIndexed;
    }

    this->Rd = Instruction::ExtractBits(assembledInstruction, 12, 15);
    this->Rn = Instruction::ExtractBits(assembledInstruction, 16, 19);

    switch (this->AddressingModeType) {
    case AddressingMode::Immediate:
    case AddressingMode::ImmediatePreIndexed:
        this->offset_12 = Instruction::ExtractBits(assembledInstruction, 0, 11);

        break;

    case AddressingMode::Register:
    case AddressingMode::RegisterPreIndexed:
        this->Rm = Instruction::ExtractBits(assembledInstruction, 0, 3);
        //this->Rs = Instruction::ExtractBits(assembledInstruction, 8,11);
        break;

    case AddressingMode::ScaledRegister:
    case AddressingMode::ScaledRegisterPreIndexed:
        this->Rm = Instruction::ExtractBits(assembledInstruction, 0, 3);
        this->shift_imm = Instruction::ExtractBits(assembledInstruction, 7, 11);
        this->shift = Instruction::ExtractBits(assembledInstruction, 5, 6);
        break;
    }

    if(shift_imm == 0)
    {
        shift_imm = 32;
    }
}
