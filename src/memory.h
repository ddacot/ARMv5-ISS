/*
 * @filename ram.h
 * @brief defines the ram class. Defines class members.
*/
#ifndef MEMORY_H
#define MEMORY_H
#include <QApplication>
class memory
{

public:

    const uint32_t MAX_MEM_SIZE = 1024000;

    //holds the size of the ram
    uint32_t MEM_SIZE;

    class cpu *cpu;
    //pointer to the memory array.
    unsigned char *MEM_Array;

    int ReadWord(uint32_t addr);
    int WriteWord(uint32_t addr, uint32_t VAL);

    int ReadHalfWord(uint32_t addr);
    int WriteHalfWord(uint32_t addr, uint16_t VAL);

    int ReadByte(uint32_t addr);
    int WriteByte(uint32_t addr, uint8_t VAL);

    bool TestFlag(uint32_t addr, uint8_t bit);
    void SetFlag(uint32_t addr, uint8_t bit, bool flag);
    int ExtractBits(int word, int startBit, int endBit);

    int fillMemory(char value, int start, uint32_t end);
    int LoadIntoMemory(char *data, int startAddr, int nrOfBytes);

    int calculateChecksum();
    void SetUpMemory(uint32_t MEM_SIZE);
    void reset();
    memory();
};

#endif // RAM_H
