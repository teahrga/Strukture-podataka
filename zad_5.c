#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

typedef struct _element {
    int broj;
    struct _element* next;
}Element;

int fileToList(Element*, Element*);
Element* lineToList(Element*, char*);
Element* findLast(Element*);
int ispis(Element*);
Element* unija(Element*, Element*, Element*);
int postoji(Element*, Element*);
int unesiSortirano(Element*, int);
Element* presjek(Element*, Element*, Element*);

int main()
{
    Element* L1, * L2, * U, * P;
    L1 = (Element*)malloc(sizeof(Element));
    L2 = (Element*)malloc(sizeof(Element));
    U = (Element*)malloc(sizeof(Element));
    P = (Element*)malloc(sizeof(Element));
    L1->next = NULL;
    L2->next = NULL;
    U->next = NULL;
    P->next = NULL;

    fileToList(L1, L2);

    printf("\nLista 1:");
    ispis(L1);
    printf("\nLista 2:");
    ispis(L2);
    U = unija(L1, L2, U);
    printf("\nUnija listi: ");
    ispis(U);
    P = presjek(L1, L2, P);
    printf("\nPresjek listi: ");
    ispis(P);

    return 0;
}

int fileToList(Element* L1, Element* L2)
{
    FILE* fp = NULL;
    char* filename = (char*)malloc(sizeof(char) * 55);

    char* line1 = (char*)malloc(sizeof(char) * 1024);
    char* line2 = (char*)malloc(sizeof(char) * 1024);

    printf("Unesite ime datoteke: ");
    scanf("%s", filename);
    if (strchr(filename, '.') == 0)
        strcat(filename, ".txt");
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("\nERROR! %s could not open!\n", filename);
        return -1;
    }

    fgets(line1, 1024, fp);
    fgets(line2, 1024, fp);

    L1 = lineToList(L1, line1);
    L2 = lineToList(L2, line2);

    fclose(fp);
    return 0;
}

Element* lineToList(Element* head, char* line)
{
    int n;

    while (*line != 0) {
        Element* q = (Element*)malloc(sizeof(Element));
        Element* last = findLast(head);
        sscanf(line, "%d %n", &q->broj, &n);
        line += n;
        q->next = NULL;
        last->next = q;
    }

    return head;
}

Element* findLast(Element* head)
{
    if (head->next == NULL)
        return head;

    else {
        while (head->next != NULL)
            head = head->next;
    }

    return head;
}

int ispis(Element* head)
{
    if (head->next == NULL) {
        printf("\nPrazna lista!\n");
        return -1;
    }

    Element* q = head->next;

    while (q != NULL) {
        printf(" %d", q->broj);
        q = q->next;
    }

    return 0;
}

Element* unija(Element* L1, Element* L2, Element* U)
{
    if (L1->next == NULL || L2->next == NULL)
        return NULL;

    Element* temp1 = L1->next;
    Element* temp2 = L2->next;

    while (temp1 != NULL) {
        if (!postoji(U, temp1))
            unesiSortirano(U, temp1->broj);
        temp1 = temp1->next;
    }

    while (temp2 != NULL) {
        if (!postoji(U, temp2))
            unesiSortirano(U, temp2->broj);
        temp2 = temp2->next;
    }

    return U;
}

int postoji(Element* head, Element* provjera)
{
    Element* temp = head->next;

    while (temp != NULL && temp->broj != provjera->broj)
        temp = temp->next;

    if (temp == NULL)
        return 0;

    return 1;
}

int unesiSortirano(Element* head, int broj)
{
    Element* temp = head;

    while (temp->next != NULL && temp->next->broj < broj)
        temp = temp->next;

    Element* new = (Element*)malloc(sizeof(Element));
    new->broj = broj;
    new->next = temp->next;
    temp->next = new;

    return 0;
}

Element* presjek(Element* L1, Element* L2, Element* P)
{
    Element* temp1 = L1->next;
    Element* temp2 = L2->next;

    while (temp1 != NULL) {
        if (postoji(L2, temp1) && !postoji(P, temp1))
            unesiSortirano(P, temp1->broj);
        temp1 = temp1->next;
    }

    while (temp2 != NULL) {
        if (postoji(L1, temp2) && !postoji(P, temp2))
            unesiSortirano(P, temp2->broj);
        temp2 = temp2->next;
    }

    return P;
}