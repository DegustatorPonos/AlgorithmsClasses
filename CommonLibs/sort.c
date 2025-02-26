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


// The length of the array must be > SortedLength + 1
void InsertInThePlace(int *array, int sortedlength, int value)
{
    bool IsPreviousGreater = true;
    bool IsInserted = false;
    for(int i = sortedlength; i > 0; i--)
    {
        if(array[i-1] > value && i > 1)
        {
            array[i] = array[i-1];
        }
        else {
            array[i] = value;
            return;
        }
    }
}

void InsersionSort(int* array, int length)
{
    for(int i = 1; i < length; i++)
    {
        InsertInThePlace(array, i, array[i]);
    }
}

void SwapSort(int* array, int length)
{
    for(int i = 0; i < length - 1; i++)
    {
        int MinPosition = i;
        int minValue = array[i];
        for(int j = i; j < length; j++)
        {
            if(array[j] < minValue)
            {
                minValue = array[j];
                MinPosition = j;
            }
        }
        swap(array, i, MinPosition);
    }
}
