/*
 * @filename ram.cpp
 * @brief the following file implements the memory class. Contains a memory array and functions
 * to perform operations on the memory.
*/

#include "memory.h"
#include <QDebug>
#include "log.h"
memory::memory()
{

}

void memory::reset()
{
    for(uint32_t i = 0; i < MEM_SIZE; i++)
    {
        MEM_Array[i] = 0;
    }
}

void memory::SetUpMemory(uint32_t MEM_SIZE)
{
    if(MEM_SIZE > MAX_MEM_SIZE)
    {
        qCritical() << ("Memory size too big.");
    }
    else
    {
        this->MEM_SIZE = MEM_SIZE;
        MEM_Array = new unsigned char[MEM_SIZE];
        for(uint32_t i = 0; i < MEM_SIZE; i++)
        {
            MEM_Array[i] = 0;
        }
    }
}
/*
 * @brief ReadWord function reads the word stored at <addr>.
 * @params adress stored in uin32_t addr
 * @return value stored in memory at address <addr>
*/

int memory::ReadWord(uint32_t addr)
{
    if(addr == 0x100001)
    {
        //qDebug() << cpu->lastCharacter;
        //emit cpu->notifier->printToConsole();
        //return cpu->lastCharacter;
        if(!cpu->keyboardInput.isEmpty())
            return cpu->keyboardInput.dequeue();
        else
            return 13;
    }
    if(addr % 4 == 0)
    {
        if(addr <= MEM_SIZE - 4)
        {
            return ((int32_t)MEM_Array[addr + 3]) << 24 | MEM_Array[addr+2] << 16 | MEM_Array[addr+1] << 8 | MEM_Array[addr];
        }
    }
}

/*
 * @brief ReadHalfWord function reads the halfword stored at <addr>.
 * @params adress stored in uin32_t addr
 * @return value stored in memory at address <addr>
*/
int memory::ReadHalfWord(uint32_t addr)
{
    if(addr == 0x100001)
    {
        //return cpu->lastCharacter;
        if(!cpu->keyboardInput.isEmpty())
            return cpu->keyboardInput.dequeue();
        else
            return 13;
    }
    if(addr % 2 == 0)
    {
        if(addr <= MEM_SIZE - 2)
        {
            return ((int16_t)MEM_Array[addr + 1]) << 8 | MEM_Array[addr];
        }
    }
}

/*
 * @brief ReadByte function reads the byte stored at <addr>.
 * @params adress stored in uin32_t addr
 * @return value stored in memory at address <addr>
*/
int memory::ReadByte(uint32_t addr)
{
    //qDebug() << "reading 0x100001";
    if(addr == 0x100001)
    {
        // qDebug() << ;
        //emit cpu->notifier->printToConsole();
        //return cpu->lastCharacter;
        if(!cpu->keyboardInput.isEmpty())
            return cpu->keyboardInput.dequeue();
        else
            return 13;
    }
    else
    {
        if(addr <= MEM_SIZE)
        {
            return ((int8_t)MEM_Array[addr]);
        }
    }

}

/*
 * @brief WriteWord function writes word in <VAL> in memory at adress <addr>.
 * @params adress stored in uin32_t addr, value is stored in uint32_t VAL
 * @return returns 0 if successful
*/
int memory::WriteWord(uint32_t addr, uint32_t VAL)
{
    if(addr == 0x100000)
    {
         emit cpu->notifier->printToConsole(QChar(VAL));
        // cpu->HLT = 1;
         //while(cpu->HLT);
         //qDebug() << cpu->lastCharacter  << VAL;
    }
    else
    {
        if(addr % 4 == 0)
        {
                if(addr <= MEM_SIZE - 4)
                {
                    for(int i = 0; i < 4; i++)
                    {
                        MEM_Array[addr + i] = (unsigned char)(VAL & 0xFF);
                        VAL = VAL >> 8;
                    }
                }
        }
    }
    return 0;
}

/*
 * @brief WriteHalfWord function writes the HalfWord in <VAL> to memory at adress <addr>.
 * @params adress stored in uin32_t addr, value is stored in uint32_t VAL
 * @return returns 0 if successful
*/
int memory::WriteHalfWord(uint32_t addr, uint16_t VAL)
{
    if(addr == 0x100000)
    {
        //cpu->lastCharacter = (char)VAL;
        emit cpu->notifier->printToConsole(QChar(VAL));
        //cpu->HLT = 1;
        //while(cpu->HLT);
         //cpu->lastCharacter = (char)VAL;
         //qDebug() << cpu->lastCharacter  << VAL;
    }
    else
    {
        if(addr % 2 == 0)
        {
            if(addr <= MEM_SIZE - 2)
            {
                for(int i = 0; i < 2; i++)
                {
                    MEM_Array[addr + i] = (unsigned char)(VAL & 0xFF);

                    VAL = VAL >> 8;
                }
            }
        }
    }
    return 0;
}

/*
 * @brief WriteByte function writes byte in <VAL> to memory at adress <addr>.
 * @pamemorys adress stored in uin32_t addr, value is stored in uint32_t VAL
 * @return returns 0 if successful
*/
int memory::WriteByte(uint32_t addr, uint8_t VAL)
{
    if(addr == 0x100000)
    {
        //cpu->lastCharacter = (char)VAL;
        emit cpu->notifier->printToConsole(QChar(VAL));
        //cpu->HLT = 1;
        //while(cpu->HLT);
        //cpu->lastCharacter = (char)VAL;
        //qDebug() << cpu->lastCharacter  << VAL;
    }
    else
    {
        if(addr < MEM_SIZE)
        {
            MEM_Array[addr] = VAL;
        }
    }
    return 0;
}

/*
 * @brief LoadIntomemory function loads a char buffer into memory buffer
 * @pamemorys adress stored in uin32_t addr, the buffer is stored in <data>, and the length of the buffer
 * in <nrOfBytes>
 * @return returns the number of bytes written to memory
*/
int memory::LoadIntoMemory(char *data, int startAddr, int nrOfBytes)
{
    int bytesWritten = 0;
    if(startAddr + nrOfBytes > MEM_SIZE)
    {
        qCritical("Can not write to memory. File too big.");
        return 1;
    }

    for(int i = 0; i < nrOfBytes; i++)
    {
        WriteByte(startAddr + i, data[i]);
        bytesWritten++;
    }

    return bytesWritten;
}

/*
 * @brief TestFlag function tests whether the bit <bit> of the value stored at <addr> is set or not
 * @params adress stored in uin32_t addr, the bit position is stored in uint8_t bit
 * @return returns true if bit is set, 0 otherwise
*/
bool memory::TestFlag(uint32_t addr, uint8_t bit)
{
    if(addr <= MEM_SIZE - 4 && bit <= 31)
    {
    uint32_t num = memory::ReadWord(addr);
    return ((num & (1 << bit)) && 1);

    }
    return false;
}

/*
 * @brief SetFlag function sets the bit <bit> to the value of <flag>
 * @params adress stored in uin32_t addr, the bit position is stored in uint8_t bit, the value of the bit
 * is stored in bool flag.
 * @return does not return.
*/
void memory::SetFlag(uint32_t addr, uint8_t bit, bool flag)
{
    if(addr <= MEM_SIZE - 4 && bit <= 31)
    {

        int num = memory::ReadWord(addr);
        if(flag)
            num = num | (1 << bit);
        else
            num = num & ~(1 << bit);

        memory::WriteWord(addr, num);
    }
}
/*
 * @brief ExtractBits function extracts the bits between <startBit> and <endBit>
 * @params the value is given by int word, the start and ending positions are given by int startBit
 * and int endBit.
 * @return returns the bit values in the interval
*/
int memory::ExtractBits(int word, int startBit, int endBit)
{
    int num = 0;
    for(int i = 0; i < 32; i++)
    {
        if(i >= startBit && i <= endBit)
        {
            num |= word & (1 << i);
        }
    }
    return num;
}

/*
 * @brief calculateChecksum function returns the checksum for the memory array
 * @params no params
 * @return returns the checksum value
*/
int memory::calculateChecksum()
{
    int cksum = 0;
    for(int i = 0; i < MEM_SIZE; i++)
    {
        cksum += MEM_Array[i] ^ i;
    }
    return cksum;
}
