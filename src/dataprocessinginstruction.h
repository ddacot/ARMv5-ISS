#ifndef DATAPROCESSINGINSTRUCTION_H
#define DATAPROCESSINGINSTRUCTION_H
#include "cpu.h"
#include "instruction.h"


class DataProcessingInstruction: public Instruction
{
public:

    DataProcessingInstruction();

    virtual void decode();
    virtual void execute();

    AddressingMode AddressingModeType;
    //declare the common bit fields in a Data Processing instruction
    int S;
    int I;
    int SBZ;
    int rotate_imm;
    int immed_8;

    int shift_imm;
    int Rs;

    int RnVal, RmVal, RsVal, RdVal;
};

#endif // DATAPROCESSINGINSTRUCTION_H
