#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NAME "input"


void ClaculateDistance(int* street, int len);

int GetFileSize(FILE *fptr)
{
    fseek(fptr, EOF, SEEK_END);
    int outp = ftell(fptr) + 1;
    rewind(fptr);
    return outp;
}

int main()
{
    FILE* fptr = fopen(FILE_NAME, "r");
    if(fptr == NULL)
    {
        printf("Error while opening the file\n");
        return 1;
    }
    int stage = 0;
    int sum = 0;
    int file_size = GetFileSize(fptr);
    int length;
    int index = 0;
    char* buf = malloc(file_size);
    int* street;
    while((buf = fgets(buf, file_size, fptr)) != NULL)
    {
        if(stage == 0)
        {
            street = malloc(sizeof(int) * atoi(buf));
            length = atoi(buf);
            stage = 1;
            continue;
        }
        char* parts = strtok(buf, " ");
        while(parts != NULL)
        {
            if(index < length)
            {
                int res = atoi(parts);
                street[index] = res;
            }
            index++;
            parts = strtok(NULL, " ");
        }
        free(parts);
    }
    ClaculateDistance(street, length);
    for(int i = 0; i < length; i++)
    {
        printf("%d ", street[i]);
    }
    printf("\n");
    free(buf);
    free(street);
    fclose(fptr);
    return 0;
}

void ClaculateDistance(int* street, int len)
{
    int distance = 0;
    for(int i = 0; i < len; i++)
    {
        if(street[i] == 0)
        {
//            printf("0 at %d\n", i);
            if(i < 1)
            {
                continue;
            }
            int reverceIndex = i - 1;
            int val = 1;
            while(street[reverceIndex] > val)
            {
//                printf("Setting value at %d to %d\n", reverceIndex, val);
                street[reverceIndex] = val;
                val++;
                reverceIndex--;
            }
            street[i] = 0;
            distance = 0;
            continue;
        }
        distance++;
        street[i] = distance;
    }
}
