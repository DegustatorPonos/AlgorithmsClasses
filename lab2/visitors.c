#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../CommonLibs/FileUtils.h"
#include "../CommonLibs/sort.h"
#define FILE_NAME "./inputs/lab2/visitors"

int GetMinutes(char *time) {
    int hrs, mins, outp;
    sscanf(time, "%d:%d", &hrs, &mins);
    outp = hrs * 60 + mins;
    return outp;
}

int main()
{
    FILE *fptr = fopen(FILE_NAME, "r");
    int FileSize = GetFileSize(fptr);
    char *buf = malloc(sizeof(char) * FileSize);
    int visitorNum = ReadIntFromFile(fptr, FileSize);

    int *Arrivals = malloc(sizeof(int) * visitorNum);
    int *Departures = malloc(sizeof(int) * visitorNum);

    for(int i = 0; i < visitorNum; i++) {
        buf = fgets(buf, FileSize, fptr);
        // printf("%s", buf);
        char *parts = strtok(buf, " ");
        Arrivals[i] = GetMinutes(parts);
        parts = strtok(NULL, " ");
        Departures[i] = GetMinutes(parts);
    }

    QuickSort(Arrivals, 0, visitorNum);
    QuickSort(Departures, 0, visitorNum);

    int currentVisitors = 0, maxVisitors = 0, currentTime;
    int depIndex = 0;
    for (int i = 0; i < visitorNum; i++) {
        int currentTime = Arrivals[i];
        while(depIndex < visitorNum && Departures[depIndex] <= currentTime){
            depIndex++;
            currentVisitors--;
        }
        currentVisitors++;
        if(currentVisitors > maxVisitors) maxVisitors = currentVisitors;
    }

    printf("%d\n", maxVisitors);
    free(buf);
    fclose(fptr);
    return 0;
}
