#ifndef ADD_H
#define ADD_H
#include "dataprocessinginstruction.h"

class ADD: public DataProcessingInstruction
{
public:
    ADD();

    void execute();
    void decode();
};

#endif // ADD_H
