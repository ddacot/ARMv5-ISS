#include "uxtb.h"
#include "instruction.h"
UXTB::UXTB() : Instruction()
{

}

void UXTB::decode()
{
    Instruction::decode();

    Rd = Instruction::ExtractBits(assembledInstruction, 12, 15);
    Rm = Instruction::ExtractBits(assembledInstruction, 0, 3);
    rotate_imm = Instruction::ExtractBits(assembledInstruction, 10, 11);

}

void UXTB::execute()
{
    int RdVal = cpu->regs->ReadWord(cpu->GET_REG_ADDR(Rd));
    int RmVal = cpu->regs->ReadWord(cpu->GET_REG_ADDR(Rm));

    if(Instruction::ExtractBits(assembledInstruction, 16, 27) == 0x6EF)
    {
        cpu->regs->WriteWord(cpu->GET_REG_ADDR(Rd), Instruction::cpu->rotr(RmVal, 8*rotate_imm) & 0x000000FF);

    }
    else
        cpu->regs->WriteWord(cpu->GET_REG_ADDR(Rd), Instruction::cpu->rotr(RmVal, 8*rotate_imm) & 0x00FF00FF);
}
