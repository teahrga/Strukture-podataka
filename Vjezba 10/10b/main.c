#include "declarations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    countryPos root = NULL;
    root = ReadFromFile("drzave.txt");

    PrintTree(root);

    SearchCities(root);

    return 0;
}