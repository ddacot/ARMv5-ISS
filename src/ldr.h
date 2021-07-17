#ifndef LDR_H
#define LDR_H
#include "loadstoreinstruction.h"

class LDR : public LoadStoreInstruction
{
public:
    LDR();
    
    void decode();
    void execute();
};

#endif // LDR_H
