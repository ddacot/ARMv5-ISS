#ifndef UHSUB_H
#define UHSUB_H
#include "instruction.h"

class UHSUB: public Instruction
{
public:
    UHSUB();

    void decode();
    void execute();

};

#endif // UHSUB_H
