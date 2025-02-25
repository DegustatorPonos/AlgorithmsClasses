#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NAME "./inputs/lab1/Polynom"

// Returns file size to assign to a buffer
int GetFileSize(FILE *fptr)
{
    fseek(fptr, EOF, SEEK_END);
    int outp = ftell(fptr) + 1;
    rewind(fptr);
    return outp;
}

typedef struct{
    long *polinomArguments;
    int Length;
    long mod;
    int CalculatedAmmount;
} POLYNOM;

POLYNOM *ParsePolynomInfo(char *inp) {
    POLYNOM *outp = malloc(sizeof(POLYNOM));
    char* parts = strtok(inp, " ");
    // Power
    outp->Length = atol(parts);
    outp->polinomArguments = malloc(sizeof(long) * (outp->Length + 1));
    parts = strtok(NULL, " ");
    // Ammount of calculated parts
    outp->CalculatedAmmount = atoi(parts);
    parts = strtok(NULL, " ");
    // mod
    outp->mod = atol(parts);
    return outp;
}

void PrintPolynom(POLYNOM *toPrint)
{
    printf("Length: %d\n", toPrint->Length);
    printf("Mod: %ld\n", toPrint->mod);
    printf("CalculatedAmmount: %d\n", toPrint->CalculatedAmmount);
    printf("Polynom: ");
    for(int i = toPrint->Length; i >= 0; i--)
    {
        printf("%ldx^%d", toPrint->polinomArguments[i], i);
        if(i > 0)
            printf(" + ");
    }
    printf("\n");
}

void CalculatePolynomResultByMod(POLYNOM *inp, long x);

int main() 
{
    FILE *fptr = fopen(FILE_NAME, "r");

    // REading polynom info from the file
    int fileLength = GetFileSize(fptr);
    char *buffer = malloc(fileLength);
    buffer = fgets(buffer, fileLength, fptr);
    POLYNOM *mainPolynom = ParsePolynomInfo(buffer);
    for(int i = mainPolynom->Length; i >= 0; i--)
    {
        buffer = fgets(buffer, fileLength, fptr);
        mainPolynom->polinomArguments[i] = atol(buffer);
    }
    PrintPolynom(mainPolynom);

    // Calculating solutions
    for(int i = 0; i < mainPolynom->CalculatedAmmount; i++)
    {
        buffer = fgets(buffer, fileLength, fptr);
        CalculatePolynomResultByMod(mainPolynom, atol(buffer));
    }


    // Free
    free(mainPolynom->polinomArguments);
    free(mainPolynom);
    free(buffer);
    fclose(fptr);
    return 0;
}

// (arg * x ^ power) % mod
long GetToPowerByMod(long arg, int power, long x, long mod)
{
    long result = arg % mod;
    for(int i = 0; i < power; i++) 
        result = (result * x) % mod;
    return result;
}

void CalculatePolynomResultByMod(POLYNOM *inp, long x)
{
    printf("Calculating polynom for value %ld\n", x);
    long returnSum = inp->polinomArguments[0]; // The x^0 is always 1 so this will always be a result
    for(int i = 1; i <= inp->Length; i++)
    {
        returnSum += GetToPowerByMod(inp->polinomArguments[i], i, x, inp->mod);
        returnSum = returnSum % inp->mod;
    }
    printf("%ld\n", returnSum);
}

