#ifndef UHADDSUBX_H
#define UHADDSUBX_H
#include "instruction.h"

class UHADDSUBX: public Instruction
{
public:
    UHADDSUBX();

    void decode();
    void execute();
};

#endif // UHADDSUBX_H
