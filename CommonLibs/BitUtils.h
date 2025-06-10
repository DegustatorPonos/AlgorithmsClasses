#include<stdbool.h>
#include <sys/types.h>
#include <stdint.h>

bool GetBitFromUInt(uint source, int bitNumber);

// Large bit contaier. Used to store more than 2^64 values
typedef struct {
    long long Size;
    uint64_t *container;
} LBS;

LBS *GenerateLBS(long long cap);
void PassValueInLBS(LBS *lbs, long long index, bool value);
bool GetValueFromLBS(LBS *lbs, long long index);
