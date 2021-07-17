#ifndef LOADSTOREINSTRUCTION_H
#define LOADSTOREINSTRUCTION_H
#include "instruction.h"



class LoadStoreInstruction : public Instruction
{
public:
    LoadStoreInstruction();

    AddressingMode AddressingModeType;
    int I;
    int P;
    int U;
    int B;
    int W;
    int L;
    int Rm;
    int shift;
    int shift_imm;
    int offset_12;
    int register_list;
    int nrOfRegisters;
    int RnVal, RmVal, RdVal;
    int address;

    void execute();
    void decode();
};

#endif // LOADSTOREINSTRUCTION_H
