// https://en.wikibooks.org/wiki/Algorithm_Implementation/Geometry/Convex_hull/Monotone_chain
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include "../CommonLibs/FileUtils.h"
#define FILE_NAME "./inputs/lab2/hull"

typedef struct {
    ushort X;
    ushort Y;
    uint64_t index;
} Point;

Point* points;
Point* hull;

void swapRecords(Point *array, int i, int j)
{
    uint64_t indBuf = array[i].index;
    ushort x = array[i].X;
    ushort y = array[i].Y;
    array[i].index = array[j].index;
    array[i].X = array[j].X;
    array[i].Y = array[j].Y;
    array[j].index = indBuf;
    array[j].X = x;
    array[j].Y = y;
}


void QuickSortPoints(Point* array, int start, int end)
{
    uint64_t pivot = array[start].index;
    // Partitioning
    int leftPos = start;
    int rightPos = end;
    while(leftPos <= rightPos)
    {
        while(array[leftPos].index < pivot)
            leftPos++;
        while(array[rightPos].index > pivot)
            rightPos--;
        if(leftPos <= rightPos)
        {
            swapRecords(array, rightPos, leftPos);
            leftPos++;
            rightPos--;
      }
    }
    // Recursion
    if(start < rightPos)
        QuickSortPoints(array, start, rightPos);
    if(leftPos < end)
        QuickSortPoints(array, leftPos, end);
}


long cross(Point O, Point A, Point B) {
    return (A.X - O.X) * (B.Y - O.Y) - (A.Y - O.Y) * (B.X - O.X);
}

// Построение выпуклой оболочки
int convex_hull(int pointsLen) {
    int k = 0;
    for (int i = 0; i < pointsLen; i++) {
        while (k >= 2 && cross(hull[k-2], hull[k-1], points[i]) <= 0) {
            k--;
        }
        hull[k++] = points[i];
    }

    int t = k + 1;
    for (int i = pointsLen  - 2; i >= 0; i--) {
        while (k >= t && cross(hull[k-2], hull[k-1], points[i]) <= 0) {
            k--;
        }
        hull[k++] = points[i];
    }

    return k - 1; 
}

double Perim(int hull_size) {
    double perimeter = 0.0;
    for (int i = 0; i < hull_size; i++) {
        double dx = hull[i].X - hull[(i + 1) % hull_size].X;
        double dy = hull[i].Y - hull[(i + 1) % hull_size].Y;
        perimeter += sqrt(dx * dx + dy * dy);
    }
    return perimeter;
}

int main() {
    FILE *fptr = fopen(FILE_NAME, "r");
    int FileSize = GetFileSize(fptr);
    char *buf = malloc(sizeof(char) * FileSize);

    int pointsLen = ReadIntFromFile(fptr, FileSize);

    points = (Point*)malloc(pointsLen * sizeof(Point));
    hull = (Point*)malloc(2 * pointsLen * sizeof(Point));

    for(int i = 0; i < pointsLen; i++) {
        buf = fgets(buf, FileSize, fptr);
        char *parts = strtok(buf, " ");
        points[i].X = atoi(parts);
        parts = strtok(NULL, " ");
        points[i].Y = atoi(parts);
        points[i].index = ((uint64_t)points[i].X << 32) + points[i].Y;
    }
    QuickSortPoints(points, 0, pointsLen - 1);

    int hull_size = convex_hull(pointsLen);
    double perimeter = Perim(hull_size);

    printf("%.2f\n", perimeter);

    free(buf);
    fclose(fptr);
    return 0;
}
