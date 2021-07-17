#ifndef SUB_H
#define SUB_H
#include "dataprocessinginstruction.h"

class SUB: public DataProcessingInstruction
{
public:
    SUB();

    void execute();
    void decode();
};

#endif // SUB_H
