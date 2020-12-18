#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

#define LINE_LEN 1024

typedef struct _polinom {
    int koeficijent;
    int eksponent;

    struct _polinom* next;
}Polinom;

int ucitajIzDat(Polinom*, Polinom*, FILE*);
Polinom* lineToList(Polinom*, char*);
Polinom* insertSorted(Polinom*, int, int);
int ispis(Polinom*);
Polinom* sumiraj(Polinom*, Polinom*, Polinom*);
Polinom* pomnozi(Polinom*, Polinom*, Polinom*);

int main()
{
    Polinom* P1, * P2, * S, * U;
    P1 = (Polinom*)malloc(sizeof(Polinom));
    P2 = (Polinom*)malloc(sizeof(Polinom));
    S = (Polinom*)malloc(sizeof(Polinom));
    U = (Polinom*)malloc(sizeof(Polinom));
    P1->next = NULL;
    P2->next = NULL;
    S->next = NULL;
    U->next = NULL;

    FILE* fp = NULL;
    char* filename = (char*)malloc(sizeof(char) * 25);

    printf("Unesite ime datoteke: ");
    scanf("%s", filename);

    if (strchr(filename, '.') == 0)
        strcat(filename, ".txt");

    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("\nERROR! %s could not open!\n", filename);
        return 0;
    }

    ucitajIzDat(P1, P2, fp);
    printf("\nPolinom 1: ");
    ispis(P1);
    printf("\nPolinom 2: ");
    ispis(P2);
    S = sumiraj(P1, P2, S);
    printf("\nSuma polinoma: ");
    ispis(S);
    U = pomnozi(P1, P2, U);
    printf("\nUmnozak polinoma: ");
    ispis(U);

    fclose(fp);
    return 0;
}

int ucitajIzDat(Polinom* P1, Polinom* P2, FILE* fp)
{
    Polinom* q = (Polinom*)malloc(sizeof(Polinom));
    char* linija = (char*)malloc(sizeof(char) * LINE_LEN);

    fgets(linija, LINE_LEN, fp);
    P1 = lineToList(P1, linija);
    fgets(linija, LINE_LEN, fp);
    P2 = lineToList(P2, linija);

    return 0;
}

Polinom* lineToList(Polinom* P, char* linija)
{
    int koeficijent, eksponent, n;

    while (*linija != 0) {
        sscanf(linija, " %d %d %n", &koeficijent, &eksponent, &n);
        linija += n;
        P = insertSorted(P, koeficijent, eksponent);
    }

    return P;
}

Polinom* insertSorted(Polinom* P, int koeficijent, int eksponent)
{
    if (P->next == NULL) {
        Polinom* new = (Polinom*)malloc(sizeof(Polinom));
        new->eksponent = eksponent;
        new->koeficijent = koeficijent;
        new->next = NULL;
        P->next = new;
        return P;
    }

    Polinom* q = P->next;

    if (eksponent > q->eksponent) {
        Polinom* new = (Polinom*)malloc(sizeof(Polinom));
        new->eksponent = eksponent;
        new->koeficijent = koeficijent;
        P->next = new;
        new->next = q;
        return P;
    }

    else {
        while (q->next != NULL && eksponent < q->next->eksponent)
            q = q->next;

        if (q->next != NULL && eksponent == q->next->eksponent)
            q->next->koeficijent += koeficijent;

        else if (eksponent == q->eksponent)
            q->koeficijent += koeficijent;

        else {
            Polinom* new = (Polinom*)malloc(sizeof(Polinom));
            new->eksponent = eksponent;
            new->koeficijent = koeficijent;
            new->next = q->next;
            q->next = new;
        }
    }

    return P;
}

int ispis(Polinom* P)
{
    if (P->next == NULL) {
        printf("\nPrazna lista.");
        return -1;
    }

    Polinom* q = P->next;

    do {
        printf("%d^%d + ", q->koeficijent, q->eksponent);
        q = q->next;
    } while (q->next != NULL);
    printf("%d^%d ", q->koeficijent, q->eksponent);

    return 0;
}

Polinom* sumiraj(Polinom* P1, Polinom* P2, Polinom* S)
{
    if (P1->next == NULL)
        return P2;
    if (P2->next == NULL)
        return P1;
    if (P1->next == NULL && P2->next == NULL)
        return NULL;

    P1 = P1->next;
    P2 = P2->next;

    while (P1 != NULL) {
        S = insertSorted(S, P1->koeficijent, P1->eksponent);
        P1 = P1->next;
    }
    while (P2 != NULL) {
        S = insertSorted(S, P2->koeficijent, P2->eksponent);
        P2 = P2->next;
    }

    return S;
}

Polinom* pomnozi(Polinom* P1, Polinom* P2, Polinom* U)
{
    Polinom* temp1 = P1->next;
    Polinom* temp2 = P2->next;

    while (temp1 != NULL) {
        temp2 = P2->next;
        while (temp2 != NULL) {
            insertSorted(U, temp1->koeficijent * temp2->koeficijent, temp1->eksponent + temp2->eksponent);
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }

    return U;
}