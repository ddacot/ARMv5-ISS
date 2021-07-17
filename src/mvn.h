#ifndef MVN_H
#define MVN_H
#include "dataprocessinginstruction.h"

class MVN: public DataProcessingInstruction
{
public:
    MVN();

    void decode();
    void execute();
};

#endif // MVN_H
