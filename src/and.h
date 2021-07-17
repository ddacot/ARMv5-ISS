#ifndef AND_H
#define AND_H
#include "dataprocessinginstruction.h"

class AND: public DataProcessingInstruction
{
public:
    AND();

    void decode();
    void execute();
};

#endif // AND_H
