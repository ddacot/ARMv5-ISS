#ifndef STM_H
#define STM_H
#include "loadstoreinstruction.h"

class STM: public LoadStoreInstruction
{
public:
    STM();

    void decode();
    void execute();
};

#endif // STM_H
