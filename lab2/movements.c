#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../CommonLibs/FileUtils.h"
#define FILE_NAME "./inputs/lab2/attr"

void PrintBoard(int **board, int x, int y);
int FindRowContaining(int **board, int x, int y, int trg);
int FindColContaining(int **board, int x, int y, int trg);
bool ValidateBoard(int **board, int x, int y);
void SwapRows(int **board, int x, int y, int a, int b);
void SwapCols(int **board, int x, int y, int a, int b);

int main()
{
    FILE *fptr = fopen(FILE_NAME, "r");
    int FileSize = GetFileSize(fptr);
    char *buf = malloc(sizeof(char) * FileSize);
    int x, y;
    fscanf(fptr, "%d %d", &x, &y);

    // int[x][y]
    int **board = malloc(sizeof(int*)*x);
    for(int i = 0; i < x; i++) {
        board[i] = malloc(sizeof(int) * y);
    }

    // Stolen from deepseek
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            fscanf(fptr, " %d", &board[i][j]);
        }
    }
    if(ValidateBoard(board, x, y)) {
        printf("0\n");
        return 0;
    }

    // Placing columns in order
    for(int i = 0; i < y; i++) {
        int trgIndex = FindColContaining(board, x, y, i);
        if(trgIndex + 1 != i)
            SwapCols(board, x, y, i-1, trgIndex);
    }

    // Placing rows
    for(int i = 0; i < x; i++) {
        int trgNum = 1 + ((x+1) * i);
        int trgIndex = FindRowContaining(board, x, y, trgNum);
        if(trgIndex != i)
            SwapRows(board, x, y, i, trgIndex);
    }

    if(!ValidateBoard(board, x, y)) {
        printf("FUCK.\n");
        return 0;
    }


    free(board);
    free(buf);
    fclose(fptr);
    return 0;
}

int FindRowContaining(int **board, int x, int y, int trg) {
    for(int row = 0; row < x; row++) {
        for(int col = 0; col < y; col++) {
            if(board[row][col] == trg)
                return row;
        }
    }
    return -1;
}

int FindColContaining(int **board, int x, int y, int trg) {
    for(int row = 0; row < x; row++) {
        for(int col = 0; col < y; col++) {
            if(board[row][col] == trg)
                return col;
        }
    }
    return -1;
}

void PrintBoard(int **board, int x, int y) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

bool ValidateBoard(int **board, int x, int y) {
    int i = 1;
    for(int row = 0; row < x; row++) {
        for(int col = 0; col < y; col++) {
            if(board[row][col] != i)
                return false;
            i++;
        }
    }
    return true;
}

// a <-> b
void SwapRows(int **board, int x, int y, int a, int b) {
    int *buf = malloc(sizeof(int) * y);
    for(int i = 0; i < y; i++) {
        buf[i] = board[a][i];
    }
    for(int i = 0; i < y; i++) {
        board[a][i] = board[b][i];
    }
    for(int i = 0; i < y; i++) {
        board[b][i] = buf[i];
    }
    free(buf);
    printf("R %d %d\n", a+1, b+1);
}

void SwapCols(int **board, int x, int y, int a, int b) {
    int *buf = malloc(sizeof(int) * y);
    for(int i = 0; i < x; i++) {
        buf[i] = board[i][a];
    }
    for(int i = 0; i < x; i++) {
        board[i][a] = board[i][b];
    }
    for(int i = 0; i < x; i++) {
        board[i][b] = buf[i];
    }
    free(buf);
    printf("C %d %d\n", a+1, b+1);
}
