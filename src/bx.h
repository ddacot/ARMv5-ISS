#ifndef BX_H
#define BX_H
#include "instruction.h"

class BX: public Instruction
{
public:
    BX();

    void decode();
    void execute();
};

#endif // BX_H
