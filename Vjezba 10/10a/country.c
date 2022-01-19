_CRT_SECURE_NO_WARNINGS
#include "country.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


; int InsertAfter(countryPos pos, countryPos newCountry)
{
    newCountry->next = pos->next;
    pos->next = newCountry;

    return 0;
}

int InsertCountry(countryPos head, countryPos newCountry)
{
    countryPos temp = head;

    while (temp->next)
    {
        if (strcmp(newCountry->name, temp->next->name) < 0)
        {
            InsertAfter(temp, newCountry);
            return EXIT_SUCCESS;
        }

        temp = temp->next;
    }

    InsertAfter(temp, newCountry);
    return EXIT_SUCCESS;
}

countryPos CreateCountry(char* name)
{
    countryPos newCountry = NULL;

    newCountry = (countryPos)malloc(sizeof(country));

    if (!newCountry)
    {
        printf("Not enough memory!\n");
        return NULL;
    }

    newCountry->name = (char*)malloc(strlen(name) + 1);

    strcpy(newCountry->name, name);
    newCountry->root = NULL;
    newCountry->next = NULL;

    return newCountry;
}


cityPos CreateCity(char* name, int population)
{
    cityPos newCity = NULL;
    newCity = (cityPos)malloc(sizeof(city));
    if (!newCity)
    {
        printf("Not enough memory!\n");
        return NULL;
    }

    newCity->name = (char*)malloc(strlen(name) + 1);
    strcpy(newCity->name, name);
    newCity->population = population;
    newCity->left = NULL;
    newCity->right = NULL;

    return newCity;
}

int CityCmp(cityPos first, cityPos second)
{
    int result = 0;

    result = first->population - second->population;

    if (!result)
    {
        result = strcmp(first->name, second->name);
    }

    return result;
}

int ReadFromFile(countryPos head, char* filename)
{
    FILE* countries = NULL;
    countryPos tempCountry = NULL;

    char* buffer = NULL;
    char* temp = NULL;
    char* countryName = NULL;
    char* cityFilename = NULL;

    int fileSize = 0;
    int read = 0;
    int state = 0;

    countryName = (char*)malloc(MAX_SIZE);
    cityFilename = (char*)malloc(MAX_SIZE);

    if (!countryName || !cityFilename)
    {
        printf("Not enough memory!\n");
        return -1;
    }

    countries = fopen(filename, "r");

    if (!countries)
    {
        printf("File not found!\n");
        return 1;
    }

    fseek(countries, 0, SEEK_END);
    fileSize = ftell(countries);
    rewind(countries);

    buffer = (char*)malloc(fileSize + 1);

    if (!buffer)
    {
        printf("Not enough memory!\n");
        return -1;
    }

    fread(buffer, fileSize, 1, countries);
    fclose(countries);

    temp = buffer;

    while (strlen(temp) > 0)
    {
        state = sscanf(temp, "%s %s %n", countryName, cityFilename, &read);
        temp += read;

        if (state == 2)
        {
            tempCountry = CreateCountry(countryName);

            if (tempCountry)
            {
                tempCountry->root = CreateTreeFromFile(cityFilename);
                InsertCountry(head, tempCountry);
            }
        }

    }

    return 0;
}

int PrintList(countryPos head)
{
    countryPos temp = head->next;

    if (!temp)
    {
        printf("List is empty!\n");
        return 1;
    }

    while (temp)
    {
        printf("%s:\n", temp->name);
        PrintLine();
        PrintDescending(temp->root);
        PrintLine();
        printf("\n");
        temp = temp->next;
    }

    return 0;
}

int InsertNode(cityPos curr, cityPos newNode)
{
    int state = 0;
    int relation = 0;
    if (!curr)
    {
        printf("Tree doesn't exist!\n");
        return 1;
    }

    relation = CityCmp(newNode, curr);

    if (!relation)
    {
        free(newNode);
        return EXIT_SUCCESS;
    }

    if (relation < 0)
    {
        if (!(curr->left))
        {
            curr->left = newNode;
            return EXIT_SUCCESS;
        }
        state = InsertNode(curr->left, newNode);
        return EXIT_SUCCESS;
    }

    else
    {
        if (!(curr->right))
        {
            curr->right = newNode;
            return EXIT_SUCCESS;
        }
        state = InsertNode(curr->right, newNode);
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}

cityPos CreateTreeFromFile(char* filename)
{
    FILE* cities = NULL;
    cityPos tempCity = NULL;
    cityPos root = NULL;

    char* buffer = NULL;
    char* temp = NULL;
    char* cityName = NULL;

    int fileSize = 0;
    int read = 0;
    int pop = 0;
    int state = 0;

    cityName = (char*)malloc(MAX_SIZE);


    cities = fopen(filename, "r");

    if (!cities)
    {
        printf("File not found!\n");
        return NULL;
    }

    fseek(cities, 0, SEEK_END);
    fileSize = ftell(cities);
    rewind(cities);

    buffer = (char*)malloc(fileSize + 1);

    if (!buffer)
    {
        printf("Not enough memory!\n");
        return NULL;
    }

    fread(buffer, fileSize, 1, cities);
    fclose(cities);

    temp = buffer;

    while (strlen(temp) > 0)
    {
        state = sscanf(temp, "%s %d %n", cityName, &pop, &read);
        temp += read;

        if (state == 2)
        {
            tempCity = CreateCity(cityName, pop);

            if (tempCity)
            {
                if (!root)
                    root = tempCity;
                else
                {
                    InsertNode(root, tempCity);
                }
            }
        }
    }

    return root;
}

void PrintLine()
{
    printf("******************************\n");
    return;
}

int PrintDescending(cityPos pos)
{
    if (pos == NULL)
        return EXIT_SUCCESS;
    PrintDescending(pos->right);
    printf("%s - Population %d\n", pos->name, pos->population);
    PrintDescending(pos->left);

    return EXIT_SUCCESS;
}

int PrintLarger(cityPos pos, int limit)
{
    if (pos == NULL)
        return EXIT_SUCCESS;

    PrintLarger(pos->left, limit);
    if (pos->population > limit)printf("%s - Population %d\n", pos->name, pos->population);
    PrintLarger(pos->right, limit);

    return EXIT_SUCCESS;
}

countryPos FindCountry(countryPos head, char* name)
{
    countryPos temp = head;
    while (temp)
    {
        if (temp->name && !strcmp(temp->name, name))
        {
            return temp;
        }

        temp = temp->next;
    }

    return NULL;
}

int SearchCities(countryPos head)
{
    char* countryName = NULL;
    countryPos toFind = NULL;
    int limit = 0;

    printf("Please choose a country: ");
    countryName = (char*)malloc(MAX_SIZE);

    fgets(countryName, MAX_SIZE, stdin);
    countryName[strcspn(countryName, "\n")] = 0;

    toFind = FindCountry(head, countryName);

    if (!toFind)
    {
        printf("Couldn't find country!\n");
        return 1;
    }

    printf("Please enter population threshold for city search: ");
    scanf("%d", &limit);

    printf("\nCities in %s with population over %d:\n", toFind->name, limit);
    PrintLine();
    PrintLarger(toFind->root, limit);

    return 0;
}