#ifndef MRS_H
#define MRS_H
#include "instruction.h"

class MRS: public Instruction
{
public:
    MRS();

    int R;
    void decode();
    void execute();

};


#endif // MRS_H
