#include "country.h"
#include <stdio.h>
#include <stdlib.h>


int main()
{
    countryPos hashTable[HASH_SIZE];

    for (int i = 0; i < HASH_SIZE; i++)
    {
        hashTable[i] = (countryPos)malloc(sizeof(country));
        hashTable[i]->name = NULL;
        hashTable[i]->root = NULL;
        hashTable[i]->next = NULL;
    }


    ReadFromFile(hashTable, "drzave.txt");

    for (int i = 0; i < HASH_SIZE; i++)
    {
        PrintList(hashTable[i]);
    }

    SearchCities(hashTable);

    return 0;
}