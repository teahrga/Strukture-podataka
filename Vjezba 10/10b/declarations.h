#pragma once

#define MAX_LINE 1024
#define MAX_SIZE 128

struct _country;
typedef struct _country* countryPos;

struct _city;
typedef struct _city* cityPos;

typedef struct _city
{
    char* name;
    int population;
    cityPos next;
}city;

typedef struct _country
{
    char* name;
    cityPos head;
    countryPos left;
    countryPos right;
}country;



countryPos CreateCountry(char*);
int InsertCountryNode(countryPos, countryPos);
countryPos FindCountry(countryPos, char*);

cityPos CreateCity(char*, int);
int CityCmp(cityPos, cityPos);
int InsertAfter(cityPos, cityPos);
int InsertCity(cityPos, cityPos);
int PrintDescending(cityPos);

cityPos CreateListFromFile(char*);
countryPos ReadFromFile(char*);

int PrintTree(countryPos);

void PrintLine();

int PrintLarger(cityPos, int);
int SearchCities(countryPos); 