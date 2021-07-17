#ifndef UXTH_H
#define UXTH_H
#include "instruction.h"

class UXTH : public Instruction
{
public:
    UXTH();
    void decode();
    void execute();

};

#endif // UXTH_H
