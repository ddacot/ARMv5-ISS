#ifndef ORR_H
#define ORR_H

#include "dataprocessinginstruction.h"
class ORR: public DataProcessingInstruction
{
public:
    ORR();

    void decode();
    void execute();
};

#endif // ORR_H
