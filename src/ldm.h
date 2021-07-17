#ifndef LDM_H
#define LDM_H
#include "loadstoreinstruction.h"

class LDM: public LoadStoreInstruction
{
public:
    LDM();

    void decode();
    void execute();
};

#endif // LDM_H
