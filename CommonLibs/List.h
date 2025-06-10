#include <stdbool.h>

// LISTS 
typedef struct{
    int *array;
    int Capacity;
    int Length;
} LIST;

LIST *ListInit();
void ClearList(LIST *list);
void AppendToList(LIST *list, int toAdd);
void AddCapacityToList(LIST *list);
void PrintListInfo(LIST *list);
void InsertAt(LIST *list, int position, int toInsert);
void RemoveAt(LIST *list, int position);
void MapSortedList(LIST *list);
void PrintIntArray(int *array, int length, bool PrintBrackets);

// RING BUFFERS
typedef struct {
    int *buffer;
    int length;
} RING_BUFFER;

RING_BUFFER *RingBufferInit(int length);
// Creates a ring buffer and fills it up with values from BaseArray.
// If UseExistingArray is false a new memory chunk will be allocated and the values will be copied
// Otherwise the provided pointer will be used as the buffer
RING_BUFFER *RingBufferInitFromArray(int length, int *baseArray, bool UseExistingArray);
// Returns the index of the required index in the array. 
// This function is required for wrapping.
int GetRingBufferIndex(RING_BUFFER *inp, int rawIndex);
// Returns the value from ring buffer. 
// The index is not required to be in the borders of the array.
int GetFromRingBuffer(RING_BUFFER *inp, int position);
// Writes the value in the ring buffer.
// The index is not required to be in the borders of the array.
void WriteInRingBuffer(RING_BUFFER *inp, int position, int value);
