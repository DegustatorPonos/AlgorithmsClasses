#include "BitUtils.h"
#include <stdint.h>
#include <stdlib.h>

// WARNING: Aimed at 64 bit machine

bool GetBitFromUInt(uint source, int bitNumber)
{
    if(bitNumber < 0 || bitNumber > 32)
        return false;
    return (source >> bitNumber) & 1;
}

LBS *GenerateLBS(long long cap) {
    LBS *outp = malloc(sizeof(LBS));
    outp->Size = cap;
    long size = cap / 64;
    if (size % 64 != 0) size++;
    outp->container = malloc(sizeof(uint64_t) * size);
    return outp;
}

void PassValueInLBS(LBS *lbs, long long index, bool value) {
    int i = index / 64;
    int addr = index % 64;
    if(value) {
        lbs->container[i] |= (uint64_t)value << addr;
    } else {
        lbs->container[i] &= (uint64_t)value << addr;
    }
    // printf("bit %d of %d container is now %d. Value: %llu\n", addr, i, (uint64_t)value, lbs->container[i]);
}

bool GetValueFromLBS(LBS *lbs, long long index) {
    int i = index / 64;
    int addr = index % 64;
    return lbs->container[i] >> addr & 1;
}
