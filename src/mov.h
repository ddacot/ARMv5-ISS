#ifndef MOV_H
#define MOV_H

#include "dataprocessinginstruction.h"

class MOV : public DataProcessingInstruction
{
public:
    MOV();

    bool N,Z,C,F;
    bool shifter_carry_out;
    void execute();
    void decode();
};

#endif // MOV_H
