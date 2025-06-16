#include <stdio.h>
#include "../CommonLibs/FileUtils.h"
#define FILE_NAME "./inputs/lab4/xerox"

int main()
{
    FILE *fptr = fopen(FILE_NAME, "r");
    int FileSize = GetFileSize(fptr);

    int N, x, y;
    fscanf(fptr, "%d %d %d", &N, &x, &y);
    // bin search
    N--;
    int left = 0;
    int right = N * (x > y ? x : y);
    int outp = right;

    while(left <= right) {
        int mid = left + (right - left) / 2;
        int copies = (mid/x) + (mid/y);
        if(copies >= N) {
            outp = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    outp += (x < y ? x : y);
    printf("%d\n", outp);

    fclose(fptr);
    return 0;
}
