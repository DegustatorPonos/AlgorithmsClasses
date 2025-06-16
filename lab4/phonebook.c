#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../CommonLibs/FileUtils.h"
#define FILE_NAME "./inputs/lab4/phone"

typedef struct {
    char *Name;
    unsigned int Number;
    bool isActive;
} USER;

int GetUserIndex(USER **book, int bookLen, char *Name);
void AddUser(USER **book, int bookLen, char *Name, unsigned int phone);

int main()
{
    FILE *fptr = fopen(FILE_NAME, "r");
    int FileSize = GetFileSize(fptr);
    char *buf = malloc(sizeof(char) * FileSize);

    USER **book = malloc(sizeof(USER*));
    int bookLen = 0;
    int CommandCount = ReadIntFromFile(fptr, FileSize);

    // Safe to assume there are no names longer than 64 characters
    char *Name = malloc(sizeof(char) * 64);
    unsigned int number;
    int index;
    for(int i = 0; i < CommandCount; i++) {
        buf = fgets(buf, FileSize, fptr);
        switch (buf[0]) {

            case 'A': // ADD
                sscanf(buf, "ADD %s %d", Name, &number);
                index = GetUserIndex(book, bookLen, Name);
                if(index != -1) {
                    if(book[index]->isActive) {
                        printf("ERROR\n");
                        break;
                    } else {
                        book[index]->isActive = true;
                        break;
                    }
                }
                AddUser(book, bookLen, Name, number);
                bookLen++;
                break;

            case 'D': // DELETE
                sscanf(buf, "DELETE %s", Name);
                index = GetUserIndex(book, bookLen, Name);
                if(index == -1) {
                    printf("ERROR\n");
                    break;
                }
                book[index]->isActive = false;
                break;

            case 'E': // EDITPHONE
                sscanf(buf, "EDITPHONE %s %d", Name, &number);
                index = GetUserIndex(book, bookLen, Name);
                if(index == -1 || !book[index]->isActive) {
                    printf("ERROR\n");
                    break;
                }
                book[index]->Number = number;
                break;

            case 'P': // PRINT
                sscanf(buf, "PRINT %s", Name);
                index = GetUserIndex(book, bookLen, Name);
                if(index == -1 || !book[index]->isActive) {
                    printf("ERROR\n");
                    break;
                }
                printf("%s %d\n", book[index]->Name, book[index]->Number);
                break;
        }
    }

    free(buf);
    fclose(fptr);
    return 0;
}

int GetUserIndex(USER **book, int bookLen, char *Name) {
    for(int i = 0; i < bookLen; i++) {
        if(strcmp(book[i]->Name, Name) == 0) {
            return i;
        }
    }
    return -1;
}

void AddUser(USER **book, int bookLen, char *Name, unsigned int phone) {
    USER *new = malloc(sizeof(USER));
    new->Name = malloc(sizeof(char) * strlen(Name));
    strcpy(new->Name, Name);
    new->Number = phone;
    new->isActive = true;
    book[bookLen] = new;
}
