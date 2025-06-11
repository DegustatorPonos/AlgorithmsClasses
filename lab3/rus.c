#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../CommonLibs/FileUtils.h"
#define FILE_NAME "./inputs/lab3/mil"

#define MAX_RECORDS 50000
#define MAX_NAME_LENGTH 20

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

int CalculateBestCity(Person **MiliList, int len, int citiesAmmount);
int GetCityIndex(Country *list, char *name);

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
        newPerson->Name = malloc(MAX_NAME_LENGTH);
        char *BaseCity = malloc(MAX_NAME_LENGTH);
        fscanf(fptr, "%s %s %llu", newPerson->Name, BaseCity, &newPerson->Balance);
        int CityIndex = GetCityIndex(cityList, BaseCity);
        if(CityIndex == -1) {
            City *newCity = malloc(sizeof(City));
            newCity->Id = cityList->CitiesAmmount;
            newCity->Name = malloc(MAX_NAME_LENGTH);
            strcpy(newCity->Name , BaseCity);
            cityList->cities[cityList->CitiesAmmount] = newCity;
            CityIndex = cityList->CitiesAmmount;
            cityList->CitiesAmmount++;
        }
        newPerson->currentCity = cityList->cities[CityIndex]->Id;
        // printf("City ID: %d\n", newPerson->currentCity);
        Forbes[i] = newPerson;
    }
    // printf("%d\n", cityList->CitiesAmmount);
    // printf("%s\n", cityList->cities[CalculateBestCity(Forbes, millAmm, cityList->CitiesAmmount)]->Name);

    // Handling transitions
    int currentDay = 0;
    int transactionsAmm;
    fscanf(fptr, "%d", &transactionsAmm);
    for(int i = 0; i < transactionsAmm; i++) {
        char *trg = malloc(MAX_NAME_LENGTH);
        int day;
        char *newCity = malloc(MAX_NAME_LENGTH);
        fscanf(fptr, "%s %d %s", trg, &day, newCity);
        for(int j = 0; j < millAmm; j++) {
            if(strcmp(Forbes[j]->Name, trg) == 0) {
                int deltaDay = day - currentDay;
                int PrevBestCity = CalculateBestCity(Forbes, millAmm, cityList->CitiesAmmount);
                cityList->cities[PrevBestCity]->DaysWealth += deltaDay;
                currentDay = day;
                Forbes[j]->currentCity = GetCityIndex(cityList, newCity);
                break;
            }
        }
        free(newCity);
        free(trg);
    }
    int PrevBestCity = CalculateBestCity(Forbes, millAmm, cityList->CitiesAmmount);
    cityList->cities[PrevBestCity]->DaysWealth += 50000-currentDay;

    for(int i = 0; i < cityList->CitiesAmmount; i++) {
        printf("%s - %d\n", cityList->cities[i]->Name, cityList->cities[i]->DaysWealth);
    }


    free(buf);
    fclose(fptr);
    return 0;
}

int CalculateBestCity(Person **MiliList, int len, int citiesAmmount) {
    unsigned long long *Wealths = malloc(sizeof(unsigned long long) * citiesAmmount);
    unsigned long long RichestCityWealth = 0;
    int RichestCityID = 0;
    for(int i = 0; i < len; i++) {
        Wealths[MiliList[i]->currentCity] += MiliList[i]->Balance;
        if(RichestCityWealth <= Wealths[MiliList[i]->currentCity]) {
            RichestCityID = MiliList[i]->currentCity;
            RichestCityWealth = Wealths[MiliList[i]->currentCity];
        }
    }
    free(Wealths);
    return RichestCityID;
}

int GetCityIndex(Country *list, char *name) {
    for(int i = 0; i < list->CitiesAmmount; i++) {
        if(strcmp(list->cities[i]->Name, name) == 0)
            return i;
    }
    return -1;
}
