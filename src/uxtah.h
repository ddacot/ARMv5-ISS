#ifndef UXTAH_H
#define UXTAH_H
#include "instruction.h"

class UXTAH: public Instruction
{
public:
    UXTAH();
    void decode();
    void execute();
};

#endif // UXTAH_H
