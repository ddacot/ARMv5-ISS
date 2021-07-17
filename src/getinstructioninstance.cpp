#include "getinstructioninstance.h"
#include "instruction.h"
#include "mov.h"
#include "add.h"
#include "mvn.h"
#include "sub.h"
#include "rsb.h"
#include "mul.h"
#include "and.h"
#include "orr.h"
#include "eor.h"
#include "bic.h"
#include "str.h"
#include "ldr.h"
#include "stm.h"
#include "ldm.h"
#include "swi.h"
#include "b.h"
#include "bx.h"
#include "cmp.h"
#include "mrs.h"
#include "msr.h"
#include "uxth.h"
#include "uxtb.h"
#include "uxtah.h"
#include "uxtab.h"
#include "uhadd.h"
#include "uhaddsubx.h"
#include "uhsub.h"
#include "uhsubaddx.h"
#include <QDebug>
/*
 * @brief GetInstruction function creates an instance of the Instruction, and returns a Base class pointer to it.
 * @params the instruction's assembled code
 * @return returns a pointer to instruction instance
*/
Instruction *GetInstructionInstance::instruction = NULL;
Instruction* GetInstructionInstance::GetInstruction(uint32_t instr)
{

    int type = Instruction::ExtractBits(instr, 26, 27);
    int opcode = Instruction::ExtractBits(instr, 21, 24);
    int bits4to7 = Instruction::ExtractBits(instr, 4,7);
    int bits25to27 = Instruction::ExtractBits(instr, 25,27);
    int bits24to27 = Instruction::ExtractBits(instr, 24,27);
    int bits20to27 = Instruction::ExtractBits(instr, 20,27);
    int bits21to24 = Instruction::ExtractBits(instr, 21,24);
    int bit22 = Instruction::ExtractBits(instr, 22,22);
    int bit20 = Instruction::ExtractBits(instr, 20,20);
    int bits20to21 = Instruction::ExtractBits(instr, 20,21);
    int bits23to27 = Instruction::ExtractBits(instr, 23,27);
    int bits16to27 = Instruction::ExtractBits(instr, 16,27);
    int bits16to19 = Instruction::ExtractBits(instr, 16,19);

    if(bits20to27 == 0x67 && bits4to7 == 5)
    {
        GetInstructionInstance::instruction = new UHSUBADDX();
    }
    if((bits20to27 == 0x67) && (bits4to7 == 7 || bits4to7 == 15))
    {
        GetInstructionInstance::instruction = new UHSUB();
    }
    else if(bits20to27 == 0x67 && bits4to7 == 3)
    {
        GetInstructionInstance::instruction = new UHADDSUBX();
    }
    else if((bits20to27 == 0x67) && (bits4to7 == 1 || bits4to7 == 9))
    {
        GetInstructionInstance::instruction = new UHADD();
    }
    else if((bits20to27 == 0x6E || bits20to27 == 0x6C) && bits4to7 == 7)
    {
        //qDebug() << "asd";
        GetInstructionInstance::instruction = new UXTAB();
    }
    else if(bits20to27 == 0x6f && bits16to19 != 0xF && bits4to7 == 7)
    {
        GetInstructionInstance::instruction = new UXTAH();
    }
    else if((bits16to27 == 0x6Cf || bits16to27 == 0x6EF) && bits4to7 == 7)
    {
        GetInstructionInstance::instruction = new UXTB();
    }
    else if(bits16to27 == 0x6Ff && bits4to7 == 7)
    {

        GetInstructionInstance::instruction = new UXTH();
    }
    else if(Instruction::ExtractBits(instr, 0, 31) == 0)
    {
        GetInstructionInstance::instruction = NULL;
    }
    else if(bits23to27 == 2 && bits20to21 == 0)
    {
        //qDebug() << "MRS";
        GetInstructionInstance::instruction = new MRS();
    }
    else if((bits23to27 == 6 && bits20to21 == 2) || (bits23to27 == 2 && bits20to21 == 2 && bits4to7 == 0))
    {
        //qDebug() << "MSR";
        GetInstructionInstance::instruction = new MSR();
    }
    else if(type == 0 && bits21to24 == 10 && bit20 == 1)
    {

        GetInstructionInstance::instruction = new CMP();
    }

    else if(bits20to27 == 18 && bits4to7 == 1)
    {
        GetInstructionInstance::instruction = new BX();
    }
    else if(type == 0 && opcode == 13)
    {
        GetInstructionInstance::instruction = new MOV();
    }
    else if(type == 0 && opcode == 4)
    {
        GetInstructionInstance::instruction = new ADD();
    }
    else if(type == 0 && opcode == 15)
    {
        GetInstructionInstance::instruction = new MVN();
    }
    else if(type == 0 && opcode == 2)
    {
        GetInstructionInstance::instruction = new SUB();
    }
    else if(type == 0 && opcode == 3)
    {
        GetInstructionInstance::instruction = new RSB();
    }
    else if(type == 0 && opcode == 0 && bits4to7 == 9)
    {
        GetInstructionInstance::instruction = new MUL();
    }
    else if(type == 0 && opcode == 0 && bits4to7 != 9)
    {
        GetInstructionInstance::instruction = new AND();
    }
    else if(type == 0 && opcode == 12)
    {
        GetInstructionInstance::instruction = new ORR();
    }
    else if(type == 0 && opcode == 1)
    {
        GetInstructionInstance::instruction = new EOR();
    }
    else if(type == 0 && opcode == 14)
    {
        GetInstructionInstance::instruction = new BIC();
    }
    else if(type == 1 && bit20 == 0)
    {
        GetInstructionInstance::instruction = new STR();
    }
    else if(type == 1 && bit20 == 1)
    {
        GetInstructionInstance::instruction = new LDR();
    }
    else if(bits25to27 == 4 && bit22 == 0 && bit20 == 1)
    {
        GetInstructionInstance::instruction = new LDM();
    }
    else if(bits25to27 == 4 && bit22 == 0 && bit20 == 0)
    {
        GetInstructionInstance::instruction = new STM();
    }
    else if(bits24to27 == 15)
    {
        GetInstructionInstance::instruction = new SWI();
    }
    else if(bits25to27 == 5)
    {
        GetInstructionInstance::instruction = new B();
    }

    if(GetInstructionInstance::instruction != NULL)
        GetInstructionInstance::instruction->assembledInstruction = instr;

    return GetInstructionInstance::instruction;
}
