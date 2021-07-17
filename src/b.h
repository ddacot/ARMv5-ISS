#ifndef B_H
#define B_H
#include "instruction.h"

class B: public Instruction
{
public:
    B();

    int address;
    void decode();
    void execute();
};

#endif // B_H
