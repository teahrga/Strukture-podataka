#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

typedef struct _element {
    int broj;

    struct _element* next;
}Element;

int giveRand();
Element* push(Element*, int);
Element* popStog(Element*);
Element* popRed(Element*);
int print(Element*);


int main()
{
    Element* stog = (Element*)malloc(sizeof(Element));
    Element* red = (Element*)malloc(sizeof(Element));
    stog->next = NULL;
    red->next = NULL;

    srand((unsigned)time(NULL));
    int i, push_s, push_r, pop_s, pop_r;

    do {
        printf("Koliko clanova stoga zelite stvoriti [1 - 1024]: ");
        scanf(" %d", &push_s);
    } while (1 > push_s || 1024 < push_s);

    for (i = 0; i < push_s; i++)
        stog = push(stog, giveRand());

    do {
        printf("Koliko clanova reda zelite stvoriti [1 - 1024]: ");
        scanf(" %d", &push_r);
    } while (1 > push_r || 1024 < push_r);

    for (i = 0; i < push_r; i++)
        red = push(red, giveRand());

    printf("\nStog: ");
    print(stog);
    printf("\nRed: ");
    print(red);
    printf("\n\n");

    do {
        printf("Koliko clanova stoga zelite izbrisati? ");
        scanf(" %d", &pop_s);
    } while (0 > pop_s || push_s < pop_s);

    for (i = 0; i < pop_s; i++)
        stog = popStog(stog);

    do {
        printf("Koliko clanova reda zelite izbrisati? ");
        scanf(" %d", &pop_r);
    } while (0 > pop_r || push_r < pop_r);

    for (i = 0; i < pop_r; i++)
        red = popRed(red);

    printf("\nStog: ");
    print(stog);
    printf("\nRed: ");
    print(red);
    printf("\n");

    return 0;
}

int giveRand()
{
    int broj, min = 10, max = 100;

    broj = (rand() % (max - min)) + min;

    return broj;
}

Element* push(Element* head, int broj)
{
    Element* new = (Element*)malloc(sizeof(Element));
    new->broj = broj;
    new->next = head->next;
    head->next = new;

    return head;
}

Element* popStog(Element* head)
{
    Element* brisi = head->next;
    head->next = brisi->next;
    free(brisi);

    return head;
}

Element* popRed(Element* head)
{
    if (head->next->next == NULL) {
        free(head->next);
        head->next = NULL;
        return head;
    }

    Element* temp = head->next;

    while (temp->next->next != NULL)
        temp = temp->next;

    Element* brisi = temp->next;
    temp->next = NULL;
    free(brisi);

    return head;
}

int print(Element* head)
{
    Element* h = head->next;

    if (h == NULL)
        return 0;

    while (h != NULL) {
        printf(" %d", h->broj);
        h = h->next;
    }

    return 0;
}