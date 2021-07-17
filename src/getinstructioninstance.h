#ifndef GETINSTRUCTIONINSTANCE_H
#define GETINSTRUCTIONINSTANCE_H
#include "instruction.h"
#include "mov.h"

class GetInstructionInstance
{
public:
    //function to return
    static Instruction* GetInstruction(uint32_t instr);
    static Instruction *instruction;
};

#endif // GETINSTRUCTIONINSTANCE_H
