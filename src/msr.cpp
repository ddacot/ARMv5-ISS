#include "msr.h"
#include <QDebug>
MSR::MSR():Instruction()
{

}

void MSR::decode()
{
    Instruction::decode();
    R = Instruction::ExtractBits(this->assembledInstruction, 22,22);
    Rd = Instruction::ExtractBits(this->assembledInstruction, 12,15);
    field_mask = Instruction::ExtractBits(this->assembledInstruction, 16,19);
    rotate_imm = Instruction::ExtractBits(this->assembledInstruction, 8,11);
    a8_bit_immediate =Instruction::ExtractBits(this->assembledInstruction, 0,7);
    Rm = Instruction::ExtractBits(this->assembledInstruction, 0,3);

    if(Instruction::ExtractBits(this->assembledInstruction, 25,25) == 1)
    {
        if(R==1)
            dissassembledInstruction = QString("%1 %2, #%3").arg("msr", "CPSR", QString::number(a8_bit_immediate));
        else
            dissassembledInstruction = QString("%1 %2, %3").arg("msr", "CPSR", regNames[Rm]);
    }
    else
    {
        if(R==1)
            dissassembledInstruction = QString("%1 %2, #%3").arg("msr", "SPSR", QString::number(a8_bit_immediate));
        else
            dissassembledInstruction = QString("%1 %2, %3").arg("msr", "SPSR", regNames[Rm]);
    }

}

void MSR::execute()
{
    uint32_t operand, byte_mask;

    if(Instruction::ExtractBits(this->assembledInstruction, 25,25) == 1)
    {
        operand = Instruction::cpu->rotr(a8_bit_immediate, 2*rotate_imm);
    }
    else
    {
        operand = cpu->regs->ReadWord(cpu->GET_REG_ADDR(Rm));
    }

    byte_mask = (Instruction::ExtractBits(field_mask, 0,0) == 1 ? 0x000000FF : 0x00000000) |
                (Instruction::ExtractBits(field_mask, 1,1) == 1 ? 0x0000FF00 : 0x00000000) |
                (Instruction::ExtractBits(field_mask, 2,2) == 1 ? 0x00FF0000 : 0x00000000) |
                (Instruction::ExtractBits(field_mask, 3,3) == 1 ? 0xFF000000 : 0x00000000) ;

    if(R == 0)
    {

        cpu->regs->WriteWord(cpu->GET_REG_ADDR(CPSR), ((cpu->regs->ReadWord(cpu->GET_REG_ADDR(CPSR)) & ~byte_mask) | (operand & byte_mask)));

        int mode = Instruction::ExtractBits(cpu->regs->ReadWord(cpu->GET_REG_ADDR(CPSR)), 0, 4);

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
    else
    {
        switch (cpu->mode)
        {
            case CPU_MODE::IRQ:
                cpu->regs->WriteWord(cpu->GET_REG_ADDR(SPSR_IRQ), ((cpu->regs->ReadWord(cpu->GET_REG_ADDR(SPSR_IRQ)) & ~byte_mask) | (operand & byte_mask)));
            break;
            case CPU_MODE::SVC:
                cpu->regs->WriteWord(cpu->GET_REG_ADDR(SPSR_SVC), ((cpu->regs->ReadWord(cpu->GET_REG_ADDR(SPSR_SVC)) & ~byte_mask) | (operand & byte_mask)));
            break;
        }
    }
}
