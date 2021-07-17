#ifndef UXTAB_H
#define UXTAB_H
#include "instruction.h"

class UXTAB: public Instruction
{
public:
    UXTAB();

    void decode();
    void execute();
};

#endif // UXTAB_H
