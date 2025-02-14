#include "sort.h"
#include <stdbool.h>

void swap(int *array, int i, int j)
{
    int buf = array[i];
    array[i] = array[j];
    array[j] = buf;
}

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

void QuickSort(int* array, int start, int end)
{
    // int pivot = array[(end + start)/2];
    int pivot = array[start];
    // Partitioning
    int leftPos = start;
    int rightPos = end;
    while(leftPos <= rightPos)
    {
        while(array[leftPos] < pivot)
            leftPos++;
        while(array[rightPos] > pivot)
            rightPos--;
        if(leftPos <= rightPos)
        {
            swap(array, rightPos, leftPos);
            leftPos++;
            rightPos--;
        }
    }
    // Recursion
    if(start < rightPos)
        QuickSort(array, start, rightPos);
    if(leftPos < end)
        QuickSort(array, leftPos, end);
}
