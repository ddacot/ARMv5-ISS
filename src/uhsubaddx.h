#ifndef UHSUBADDX_H
#define UHSUBADDX_H
#include "instruction.h"

class UHSUBADDX: public Instruction
{
public:
    UHSUBADDX();

    void execute();
    void decode();
};

#endif // UHSUBADDX_H
