#include "uhadd.h"

UHADD::UHADD(): Instruction()
{

}

void UHADD::decode()
{
    Instruction::decode();

    Rd = Instruction::ExtractBits(assembledInstruction, 12, 15);
    Rm = Instruction::ExtractBits(assembledInstruction, 0, 3);
    rotate_imm = Instruction::ExtractBits(assembledInstruction, 10, 11);
    Rn = Instruction::ExtractBits(assembledInstruction, 16, 19);
    //dissassembledInstruction
}

void UHADD::execute()
{
    int RdVal = cpu->regs->ReadWord(cpu->GET_REG_ADDR(Rd));
    int RmVal = cpu->regs->ReadWord(cpu->GET_REG_ADDR(Rm));
    int RnVal = cpu->regs->ReadWord(cpu->GET_REG_ADDR(Rn));
    if(Instruction::ExtractBits(assembledInstruction, 4, 7) == 1)
    {
        uint sum = Instruction::ExtractBits(RnVal, 0, 15) + Instruction::ExtractBits(RmVal, 0, 15);
        uint Rd0to15, Rd16to31;
        Rd0to15 = Instruction::ExtractBits(sum, 1, 16);
        sum = (Instruction::ExtractBits(RnVal, 16, 31) + Instruction::ExtractBits(RmVal, 16, 31));
        Rd16to31 = Instruction::ExtractBits(sum, 1, 16) << 16;

        int RdFinal = Rd0to15 | Rd16to31;
        cpu->regs->WriteWord(cpu->GET_REG_ADDR(Rd), RdFinal);


    }
    else
    {
        uint sum = Instruction::ExtractBits(RnVal, 0, 7) + Instruction::ExtractBits(RmVal, 0, 7);
        uint Rd0to7, Rd8to15,Rd16to23, Rd24to31;
        Rd0to7 = Instruction::ExtractBits(sum, 1, 8);


        sum = (Instruction::ExtractBits(RnVal, 8, 15) + Instruction::ExtractBits(RmVal, 8, 15));
        Rd8to15 = Instruction::ExtractBits(sum, 1, 8) << 8;

        sum = (Instruction::ExtractBits(RnVal, 16, 23) + Instruction::ExtractBits(RmVal, 16, 23));
        Rd16to23 = Instruction::ExtractBits(sum, 1, 8) << 16;

        sum = (Instruction::ExtractBits(RnVal, 24, 31) + Instruction::ExtractBits(RmVal, 24, 31));
        Rd24to31 = Instruction::ExtractBits(sum, 1, 8) << 24;


        int RdFinal = Rd0to7 | Rd8to15 | Rd16to23 | Rd24to31;
        cpu->regs->WriteWord(cpu->GET_REG_ADDR(Rd), RdFinal);

    }
}
