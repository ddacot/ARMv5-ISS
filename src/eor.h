#ifndef EOR_H
#define EOR_H
#include "dataprocessinginstruction.h"

class EOR: public DataProcessingInstruction
{
public:
    EOR();

    void decode();
    void execute();
};

#endif // EOR_H
