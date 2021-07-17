#ifndef RSB_H
#define RSB_H
#include "dataprocessinginstruction.h"

class RSB: public DataProcessingInstruction
{
public:
    RSB();

    void execute();
    void decode();
};

#endif // RSB_H
