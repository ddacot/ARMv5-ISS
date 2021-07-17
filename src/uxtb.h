#ifndef UXTB16_H
#define UXTB16_H
#include "instruction.h"

class UXTB: public Instruction
{
public:
    UXTB();

    void decode();
    void execute();
};

#endif // UXTB16_H
