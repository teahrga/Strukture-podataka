#include "declarations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    newCountry->head = NULL;
    newCountry->left = NULL;
    newCountry->right = NULL;

    return newCountry;
}

int InsertCountryNode(countryPos curr, countryPos newNode)
{
    int state = 0;
    int compare = 0;
    if (!curr)
    {
        curr = newNode;
        return EXIT_SUCCESS;
    }

    compare = strcmp(newNode->name, curr->name);

    if (!compare)
    {
        free(newNode);
        return EXIT_SUCCESS;
    }

    if (compare < 0)
    {
        if (!(curr->left))
        {
            curr->left = newNode;
            return EXIT_SUCCESS;
        }
        state = InsertCountryNode(curr->left, newNode);
        return EXIT_SUCCESS;
    }

    else
    {
        if (!(curr->right))
        {
            curr->right = newNode;
            return EXIT_SUCCESS;
        }
        state = InsertCountryNode(curr->right, newNode);
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}

countryPos FindCountry(countryPos root, char* name)
{
    countryPos curr = root;

    while (curr)
    {
        if (!strcmp(name, curr->name))
        {
            return curr;
        }

        if (strcmp(name, curr->name) < 0)
        {
            curr = curr->left;
        }

        else
        {
            curr = curr->right;
        }
    }

    return curr;
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
    newCity->next = NULL;

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

int InsertAfter(cityPos pos, cityPos newCity)
{
    newCity->next = pos->next;
    pos->next = newCity;

    return 0;
}

int InsertCity(cityPos head, cityPos newCity)
{
    cityPos temp = head;

    while (temp->next)
    {
        if (CityCmp(newCity, temp->next) < 0)
        {
            InsertAfter(temp, newCity);
            return EXIT_SUCCESS;
        }

        temp = temp->next;
    }

    InsertAfter(temp, newCity);
    return EXIT_SUCCESS;
}

void PrintLine()
{
    printf("******************************\n");
    return;
}

int PrintDescending(cityPos curr)
{
    if (!curr)
    {
        return 0;
    }

    else
    {
        PrintDescending(curr->next);
        if (curr->name)printf("%s - Population %d\n", curr->name, curr->population);
    }

    return 0;
}

cityPos CreateListFromFile(char* filename)
{
    FILE* cities = NULL;
    cityPos tempCity = NULL;
    cityPos head = NULL;

    char* buffer = NULL;
    char* temp = NULL;
    char* cityName = NULL;

    int fileSize = 0;
    int read = 0;
    int pop = 0;
    int state = 0;

    cityName = (char*)malloc(MAX_SIZE);
    head = (cityPos)malloc(sizeof(city));
    head->name = NULL;
    head->population = 0;
    head->next = NULL;

    if (!head || !cityName)
    {
        printf("Not enough memory!\n");
        return NULL;
    }

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
                InsertCity(head, tempCity);
            }
        }
    }

    return head;
}

int PrintTree(countryPos curr)
{
    if (!curr)
    {
        return 0;
    }

    PrintTree(curr->left);
    printf("%s:\n", curr->name);
    PrintLine();
    PrintDescending(curr->head);
    PrintLine();
    printf("\n");
    PrintTree(curr->right);

    return 0;
}

countryPos ReadFromFile(char* filename)
{
    FILE* countries = NULL;
    countryPos tempCountry = NULL;
    countryPos root = NULL;

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
        return NULL;
    }

    countries = fopen(filename, "r");

    if (!countries)
    {
        printf("File not found!\n");
        return NULL;
    }

    fseek(countries, 0, SEEK_END);
    fileSize = ftell(countries);
    rewind(countries);

    buffer = (char*)malloc(fileSize + 1);

    if (!buffer)
    {
        printf("Not enough memory!\n");
        return NULL;
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
                tempCountry->head = CreateListFromFile(cityFilename);
                if (!root)
                {
                    root = tempCountry;
                }
                else
                {
                    InsertCountryNode(root, tempCountry);
                }

            }
        }

    }

    return root;
}

int PrintLarger(cityPos pos, int limit)
{
    if (pos == NULL)
        return EXIT_SUCCESS;

    while (pos)
    {
        if (pos->population > limit)
            printf("%s - Population %d\n", pos->name, pos->population);
        pos = pos->next;
    }

    return EXIT_SUCCESS;
}

int SearchCities(countryPos root)
{
    char* countryName = NULL;
    countryPos toFind = NULL;
    int limit = 0;

    printf("Please choose a country: ");
    countryName = (char*)malloc(MAX_SIZE);

    fgets(countryName, MAX_SIZE, stdin);
    countryName[strcspn(countryName, "\n")] = 0;

    toFind = FindCountry(root, countryName);

    if (!toFind)
    {
        printf("Couldn't find country!\n");
        return 1;
    }

    printf("Please enter population threshold for city search: ");
    scanf("%d", &limit);

    printf("\nCities in %s with population over %d:\n", toFind->name, limit);
    PrintLine();
    PrintLarger(toFind->head, limit);

    return 0;
}