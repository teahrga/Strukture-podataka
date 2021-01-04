#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

#define WORD_LEN 55
#define LINE_LEN 1024

typedef struct _Element {
    float broj;

    struct _Element* next;
}Element;

Element* Push(Element*, float);
float Pop(Element*);
Element* readFile(Element*, char*);
Element* operation(Element*, char);

int main()
{
    char* filename = (char*)malloc(sizeof(WORD_LEN));
    Element* head = (Element*)malloc(sizeof(Element));
    head->next = NULL;

    printf("Unesite ime datoteke\n--> ");
    scanf("%s", filename);

    if (strchr(filename, '.') == 0)
        strcat(filename, ".txt");

    head = readFile(head, filename);

    printf("Rjesenje je: %lf", head->next->broj);

    return 0;
}

Element* Push(Element* head, float broj)
{
    Element* new = (Element*)malloc(sizeof(Element));
    new->broj = broj;
    new->next = head->next;
    head->next = new;

    return head;
}

float Pop(Element* head)
{
    float broj;

    if (head->next == NULL) {
        printf("\nPrazan stog!\n");
        return 0;
    }

    else {
        Element* temp = head->next;
        broj = temp->broj;
        head->next = temp->next;
        free(temp);
    }

    return broj;
}

Element* readFile(Element* head, char* filename)
{
    char* line = (char*)malloc(sizeof(char) * LINE_LEN);
    int n;
    float broj;
    char operacija;
    FILE* fp = NULL;

    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("\nFATAL ERROR! File %s could not open!\n");
        return NULL;
    }

    fgets(line, LINE_LEN, fp);

    while (*line != 0) {

        if (sscanf(line, " %f %n", &broj, &n) == 1) {
            Push(head, broj);
            line += n;
        }

        else {
            sscanf(line, "%c %n", &operacija, &n);
            head = operation(head, operacija);
            line += n;
        }
    }

    return head;
}

Element* operation(Element* head, char znak)
{
    float br1, br2;

    br1 = Pop(head);
    br2 = Pop(head);

    switch (znak) {
    case '+':
        head = Push(head, br2 + br1);
        break;

    case '-':
        head = Push(head, br2 - br1);
        break;

    case '*':
        head = Push(head, br2 * br1);
        break;

    case '/':
        if (br1 == 0) {
            printf("\nNemoguca operacija!\n");
            return NULL;
        }
        else
        {
            head = Push(head, br2 / br1);
        }
        break;

    default:
        printf("\nERROR! Pogresan znak operacije!\n");
        return NULL;
    }

    return head;
}