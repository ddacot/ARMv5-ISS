#ifndef CMP_H
#define CMP_H
#include "dataprocessinginstruction.h"

class CMP : public DataProcessingInstruction
{
public:
    CMP();
    int sign_immed_24;
    void decode();
    void execute();
};

#endif // CMP_H
