#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "cpu.h"

enum class AddressingMode
{
    //DataProcessingInstruction
    Immediate,
    Register,
    LSLImmediate,
    LSLRegister,
    LSRImmediate,
    LSRRegister,
    ASRImmediate,
    ASRRegister,
    RORImmediate,
    RORRegister,
    RORExtend,
    //LoadStoreInstruction
    ScaledRegister,
    ImmediatePreIndexed,
    RegisterPreIndexed,
    ScaledRegisterPreIndexed,
    //Stack
    StackFullDescending

};

enum class ShiftMode
{
    LSL,
    LSR,
    ASR,
    ROR,
    RRX
};


class Instruction
{
public:
    Instruction();
    virtual ~Instruction();
    const QString regNames[16] = {"r0", "r1", "r2","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","r13","r14","r15"};

    static unsigned int ExtractBits(uint32_t word, int startBit, int endBit);
    unsigned int countSetBits(unsigned int n);
    virtual void execute();
    virtual void decode();
    //pointer to the current cpu instance
    static cpu *cpu;

    //the instruction in machine code
    unsigned int assembledInstruction;
    QString dissassembledInstruction;
    //QString a= "s";
    //most common instruction fields
    int opcode;
    unsigned int condition;
    int signed_immed_24;
    int Rn;
    int Rm;
    int L;
    int Rd;
    int result;
    int operand2;
    int RnVal, RmVal, RsVal;
    int64_t result64;
    int rotate_imm;
};

#endif // INSTRUCTION_H
