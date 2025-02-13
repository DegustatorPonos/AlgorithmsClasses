#include "sort.h"
#include <stdbool.h>

void Bubblesort(int* array, int length)
{
    if(length < 2)
        return;
    bool IsSorted = false;
    while(!IsSorted)
    {
        IsSorted = true;
        int index = 0;
        if(index == length - 1)
            continue;
        for(int i = 0; i < length - 1; i++)
        {
            if(array[i] > array[i+ 1])
            {
                IsSorted = false;
                int buffer = array[i];
                array[i] = array[i+ 1];
                array[i+ 1] = buffer;
            }
        }
    }
}
