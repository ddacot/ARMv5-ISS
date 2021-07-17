#ifndef STR_H
#define STR_H
#include "loadstoreinstruction.h"

class STR: public LoadStoreInstruction
{
public:
    STR();

    void decode();
    void execute();
};

#endif // STR_H
