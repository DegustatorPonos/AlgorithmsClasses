#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../CommonLibs/FileUtils.h"
#define FILE_NAME "./inputs/lab3/mil"

#define MAX_RECORDS 50000

typedef struct {
    char *Name;
    int Id;
    int DaysWealth;
} City;

typedef struct {
    char *Name;
    unsigned long long Balance;
    int currentCity;
} Person;

typedef struct {
    City **cities;
    int CitiesAmmount;
} Country;

int GetCityIndex(Country *list, char *name) {
    for(int i = 0; i < list->CitiesAmmount; i++) {
        if(strcmp(list->cities[i]->Name, name) == 0)
            return i;
    }
    return -1;
}

int CalculateBestCity(Person **MiliList, int len, int citiesAmmount);

int main()
{
    FILE *fptr = fopen(FILE_NAME, "r");
    int FileSize = GetFileSize(fptr);
    char *buf = malloc(sizeof(char) * FileSize);

    Country *cityList = malloc(sizeof(Country));
    cityList->cities = malloc(sizeof(City*) * MAX_RECORDS);

    // Reading names
    int millAmm = ReadIntFromFile(fptr, FileSize);
    Person **Forbes = malloc(sizeof(Person*) * millAmm);
    for(int i = 0; i < millAmm; i++) {
        Person *newPerson = malloc(sizeof(Person));
        newPerson->Name = malloc(20);
        char *BaseCity = malloc(20);
        fscanf(fptr, "%s %s %llu", newPerson->Name, BaseCity, &newPerson->Balance);
        int CityIndex = GetCityIndex(cityList, BaseCity);
        if(CityIndex == -1) {
            City *newCity = malloc(sizeof(City));
            newCity->Id = cityList->CitiesAmmount;
            newCity->Name = malloc(20);
            strcpy(newCity->Name , BaseCity);
            cityList->cities[cityList->CitiesAmmount] = newCity;
            CityIndex = cityList->CitiesAmmount;
            cityList->CitiesAmmount++;
        }
        newPerson->currentCity = cityList->cities[CityIndex]->Id;
        printf("City ID: %d\n", newPerson->currentCity);
        Forbes[i] = newPerson;
    }
    printf("%d\n", cityList->CitiesAmmount);
    printf("%s\n", cityList->cities[CalculateBestCity(Forbes, millAmm, cityList->CitiesAmmount)]->Name);

    free(buf);
    fclose(fptr);
    return 0;
}

int CalculateBestCity(Person **MiliList, int len, int citiesAmmount) {
    unsigned long long *Wealths = malloc(sizeof(unsigned long long) * citiesAmmount);
    unsigned long long RichestCityWealth = 0;
    int RichestCityID = 0;
    for(int i = 0; i < len; i++) {
        printf("Current city ID - %d\n", MiliList[i]->currentCity);
        Wealths[MiliList[i]->currentCity] += MiliList[i]->Balance;
        if(RichestCityWealth < Wealths[MiliList[i]->currentCity]) {
            RichestCityID = i;
            RichestCityWealth = Wealths[MiliList[i]->currentCity];
        }
    }
    for(int i = 0; i < citiesAmmount; i++) {
        printf("%llu ", Wealths[i]);
    }
    printf("\n");
    free(Wealths);
    return RichestCityID;
}
