#include "sort.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// ALGO: https://en.wikipedia.org/wiki/Quicksort

int Partition(int* array, int length, int pivot)
{
    int leftIndex = 0;
    int rightIndex = length - 2; // The last one is pivot
    // Hoare partitioning
    while(rightIndex - leftIndex >= 1)
    {
        if(array[leftIndex] >= pivot && array[rightIndex] <= pivot)
        {
            printf("Swapped\n");
            swap(array, leftIndex, rightIndex);
        }
        if(array[leftIndex] <= pivot)
            leftIndex++;
        if(array[rightIndex] >= pivot)
            rightIndex--;
    }
    // Determining a new pivot position
    int newPivotPos = 0;
    for(int i = 0; i < length; i++)
    {
        newPivotPos = i;
        if(array[i] > pivot)
            break;
    }
    for(int i = length; i >= newPivotPos; i--)
        array[i] = array[i - 1];
    array[newPivotPos] = pivot;
    return newPivotPos;
}

void QuickSort(int* array, int length)
{
    if(length < 1)
        return;
    if(length == 2)
    {
        if(array[0] > array[1])
            swap(array, 0, 1);
        return;
    }
    int pivot = array[length - 1];
    // Partitioning
    int pivotPos = Partition(array, length, pivot);
    // Separation
    int leftSizeLength = pivotPos;
    int rightSizeLength = length - pivotPos - 1;
    if(leftSizeLength > 0)
    {
        int *leftSize = malloc(sizeof(int)*leftSizeLength);
        memcpy(leftSize, array, sizeof(int)*leftSizeLength);
        QuickSort(leftSize, leftSizeLength);
        memcpy(array, leftSize, sizeof(int)*leftSizeLength);
        // free(leftSize);
    }
    if(rightSizeLength > 0)
    {
        int *rightSize = malloc(sizeof(int)*rightSizeLength);
        memcpy(rightSize, &array[pivotPos + 1], sizeof(int)*rightSizeLength);
        QuickSort(rightSize, rightSizeLength);
        memcpy(&array[pivotPos + 1], rightSize, sizeof(int)*rightSizeLength);
        // free(rightSize);
    }
}
