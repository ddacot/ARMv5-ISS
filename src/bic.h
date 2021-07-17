#ifndef BIC_H
#define BIC_H
#include "dataprocessinginstruction.h"

class BIC: public DataProcessingInstruction
{
public:
    BIC();

    void decode();
    void execute();

};

#endif // BIC_H
