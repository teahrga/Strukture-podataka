#pragma once

#define MAX_LINE 1024
#define MAX_SIZE 128
#define HASH_SIZE 11

struct _country;
typedef struct _country* countryPos;

struct _city;
typedef struct _city* cityPos;

typedef struct _city
{
    char* name;
    int population;
    cityPos left;
    cityPos right;
}city;

typedef struct _country
{
    char* name;
    cityPos root;
    countryPos next;
}country;



countryPos CreateCountry(char*);
int InsertCountry(countryPos, countryPos);
int InsertAfter(countryPos, countryPos);
countryPos FindCountry(countryPos, char*);

cityPos CreateCity(char*, int);
int CityCmp(cityPos, cityPos);

int ReadFromFile(countryPos[], char*);
int PrintList(countryPos);

cityPos CreateTreeFromFile(char*);
int InsertNode(cityPos, cityPos);
int PrintDescending(cityPos);
int PrintLarger(cityPos, int);
void PrintLine();

int SearchCities(countryPos[]);