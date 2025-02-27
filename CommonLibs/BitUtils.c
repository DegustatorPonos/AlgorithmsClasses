#include "BitUtils.h"

// WARNING: Aimed at 64 bit machine

bool GetBitFromUInt(uint source, int bitNumber)
{
    if(bitNumber < 0 || bitNumber > 32)
        return false;
    return (source >> bitNumber) & 1;
}

