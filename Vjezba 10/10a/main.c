#include "country.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    countryPos head = NULL;


    head = (countryPos)malloc(sizeof(country));
    head->name = NULL;
    head->root = NULL;
    head->next = NULL;

    ReadFromFile(head, "drzave.txt");

    PrintList(head);

    SearchCities(head);

    return 0;
}