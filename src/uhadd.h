#ifndef UHADD_H
#define UHADD_H

#include "instruction.h"
class UHADD: public Instruction
{
public:
    UHADD();

    void decode();
    void execute();
};

#endif // UHADD_H
