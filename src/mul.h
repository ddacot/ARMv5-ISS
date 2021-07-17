#ifndef MUL_H
#define MUL_H
#include "dataprocessinginstruction.h"

class MUL: public DataProcessingInstruction
{
public:
    MUL();

    void decode();
    void execute();
};

#endif // MUL_H
