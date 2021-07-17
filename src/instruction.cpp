#include "instruction.h"
#include "cpu.h"

//cpu* Instruction::cpu = NULL;

Instruction::~Instruction()
{

}
Instruction::Instruction()
{

}

void Instruction::execute()
{

}

void Instruction::decode()
{
    this->condition = Instruction::ExtractBits(assembledInstruction, 28, 31);
}

unsigned int Instruction::ExtractBits(uint32_t word, int startBit, int endBit)
{
    unsigned int num = 0;
    for(int i = 0; i < 32; i++)
    {
        if(i >= startBit && i <= endBit)
        {
            num |= word & (1 << i);
        }
    }
    return num >> startBit;
}

unsigned int Instruction::countSetBits(unsigned int n)
{
  unsigned int count = 0;
  while (n)
  {
    count += n & 1;
    n >>= 1;
  }
  return count;
}
