#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../CommonLibs/FileUtils.h"
#define FILE_NAME "./inputs/lab4/cache"

typedef struct {
    long long value;
    int next_occurrence;  
} CacheEntry;

int GetNextOccurence(long long* requests, int current_index, int M, long long value);

int main()
{
    FILE *fptr = fopen(FILE_NAME, "r");
    int FileSize = GetFileSize(fptr);
    char *buf = malloc(sizeof(char) * FileSize);

    int N, M;
    fscanf(fptr, "%d %d", &N, &M);

    long long* requests = (long long*)malloc(M * sizeof(long long));
    for (int i = 0; i < M; i++) {
        fscanf(fptr, "%lld", &requests[i]);
    }

    CacheEntry* cache = (CacheEntry*)malloc(N * sizeof(CacheEntry));
    int cache_size = 0;
    int misses = 0;

    for (int i = 0; i < M; i++) {
        long long current_request = requests[i];
        bool found_in_cache = false;

        // Searching in cache
        for (int j = 0; j < cache_size; j++) {
            if (cache[j].value == current_request) {
                found_in_cache = true;
                cache[j].next_occurrence = GetNextOccurence(requests, i, M, current_request);
                break;
            }
        }

        if (!found_in_cache) {
            misses++;
            if (cache_size < N) {
                cache[cache_size].value = current_request;
                cache[cache_size].next_occurrence = GetNextOccurence(requests, i, M, current_request);
                cache_size++;
            } else {
                int farthest_index = 0;
                for (int j = 1; j < N; j++) {
                    if (cache[j].next_occurrence > cache[farthest_index].next_occurrence) {
                        farthest_index = j;
                    }
                }
                cache[farthest_index].value = current_request;
                cache[farthest_index].next_occurrence = GetNextOccurence(requests, i, M, current_request);
            }
        }
    }    

    printf("%d\n", misses);

    free(buf);
    fclose(fptr);
    return 0;
}

int GetNextOccurence(long long* requests, int current_index, int M, long long value) {
    for (int i = current_index + 1; i < M; i++) {
        if (requests[i] == value) {
            return i;
        }
    }
    return M; 
}

