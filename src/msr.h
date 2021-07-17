#ifndef MSR_H
#define MSR_H
#include "instruction.h"

class MSR: public Instruction
{
public:
    MSR();
    int R;
    int a8_bit_immediate;
    int field_mask;
    int rotate_imm;
    void decode();
    void execute();
};

#endif // MSR_H
