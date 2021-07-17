#ifndef SWI_H
#define SWI_H
#include "instruction.h"

class SWI: public Instruction
{
public:
    SWI();
    bool displayChar, halt;
    int immed_24;
    void decode();
    void execute();
};

#endif // SWI_H
