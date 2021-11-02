#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

#define WORD_LEN 55

typedef struct _student {
    char* ime;
    char* prezime;
    int godina;

    struct _student* next;
}Student;

Student* allocateNewStudent();
int Menu(Student*);
Student* addBeginning(Student*);
Student* addEnding(Student*);
Student* findLast(Student*);
Student* findPrevious(Student*, Student*);
int printList(Student*);
int printStudent(Student*);
Student* findByLastname(Student*, char*);
Student* delete(Student*, Student*);
Student* addBehind(Student*, Student*);
Student* addBefore(Student*, Student*);
int sort(Student*);
int zamjena(Student*, Student*, Student*);
Student* readFromFile(Student*);
Student* fileToList(Student*, FILE*);
int listToFile(Student*);

int main()
{
    Student* head = allocateNewStudent();
    int status = 0;

    do {
        status = Menu(head);
    } while (!status);

    return 0;
}

Student* allocateNewStudent()
{
    Student* q;

    q = (Student*)malloc(sizeof(Student));
    q->ime = (char*)malloc(sizeof(char) * WORD_LEN);
    q->prezime = (char*)malloc(sizeof(char) * WORD_LEN);
    q->next = NULL;

    return q;
}

int Menu(Student* head)
{
    int izbor;

    char* prezime = (char*)malloc(sizeof(char) * WORD_LEN);
    Student* findByLast;

    char* brisanje = (char*)malloc(sizeof(char) * WORD_LEN);
    Student* brisi;

    char* dodajIza = (char*)malloc(sizeof(char) * WORD_LEN);
    Student* iza;

    char* dodajIspred = (char*)malloc(sizeof(char) * WORD_LEN);
    Student* ispred;

    printf("****************************************\n");
    printf("-1) Izadite iz programa\n");
    printf("0) Ispisite menu\n");
    printf("1) Unesite element na pocetak\n");
    printf("2) Unesite element na kraj\n");
    printf("3) Ispisite sve elemente iz liste\n");
    printf("4) Pronadi element po prezimenu\n");
    printf("5) Izbrisite element\n");
    printf("6) Dodajte element iza odredenog elementa\n");
    printf("7) Dodajte element ispred odredenog elementa\n");
    printf("8) Sortirajte listu po prezimenu\n");
    printf("9) Procitajte iz datoteke\n");
    printf("10) Ispisite listu u datoteku\n");
    printf("****************************************\n");

    while (1) {
        printf("\n--> ");
        scanf(" %d", &izbor);

        switch (izbor) {
        case (0):
            return 0;
        case (-1):
            return 1;
        case (1): head = addBeginning(head);
            break;
        case (2): head = addEnding(head);
            break;
        case (3): printList(head);
            break;
        case (4):
            printf("\nKoje prezime zelite pronaci?\n--> ");
            scanf("%s", prezime);
            findByLast = findByLastname(head, prezime);
            printStudent(findByLast);
            break;
        case (5):
            printf("\nKoji element zelite izbrisati?\n--> ");
            scanf("%s", brisanje);
            brisi = findByLastname(head, brisanje);
            head = delete(head, brisi);
            break;
        case (6):
            printf("\nIza kojeg elementa zelite dodati?\n--> ");
            scanf("%s", dodajIza);
            iza = findByLastname(head, dodajIza);
            head = addBehind(head, iza);
            break;
        case (7):
            printf("\nIspred kojeg elementa zelite dodati?\n--> ");
            scanf("%s", dodajIspred);
            ispred = findByLastname(head, dodajIspred);
            head = addBefore(head, ispred);
            break;
        case (8):
            sort(head);
            break;
        case (9):
            head = readFromFile(head);
            break;
        case (10):
            listToFile(head);
            break;
        default:
            printf("\nKrivi unos!\n");
            return 0;
        }
    }

    return 0;
}

Student* addBeginning(Student* head)
{
    Student* q;
    q = allocateNewStudent();

    printf("\nUnesite ime: ");
    scanf("%s", q->ime);
    printf("Unesite prezime: ");
    scanf("%s", q->prezime);
    printf("Unesite godinu rodenja: ");
    scanf(" %d", &q->godina);

    q->next = head->next;
    head->next = q;

    return head;
}

Student* addEnding(Student* head)
{
    Student* q;
    Student* last;
    q = allocateNewStudent();

    printf("\nUnesite ime: ");
    scanf("%s", q->ime);
    printf("Unesite prezime: ");
    scanf("%s", q->prezime);
    printf("Unesite godinu rodenja: ");
    scanf(" %d", &q->godina);

    last = findLast(head);

    last->next = q;

    return head;
}

Student* findLast(Student* head)
{
    Student* q;

    if (head->next == NULL)
        return head;

    q = head->next;

    while (q->next != NULL)
        q = q->next;

    return q;
}

Student* findPrevious(Student* head, Student* element)
{
    Student* q;

    if (head->next == NULL) {
        return head;
    }

    q = head;

    if (q->next == NULL)
        return q;

    while (q != NULL && strcmp(q->next->prezime, element->prezime) != 0)
        q = q->next;

    if (q == NULL) {
        printf("\nFATAL ERROR! Element nije pronaden!\n");
        return head;
    }

    return q;
}

int printList(Student* head)
{
    Student* q;

    if (head->next == NULL) {
        printf("\nPrazna lista!");
        return 0;
    }

    q = head->next;

    printf("\n***************VASA LISTA***************\n");

    while (q != NULL) {
        printf("%-15s\t%-15s\t%-4d\n", q->ime, q->prezime, q->godina);
        q = q->next;
    }

    printf("****************************************\n");

    return 0;
}

int printStudent(Student* person)
{
    printf("****************************************\n");
    printf("%-15s\t%-15s\t%-4d\n", person->ime, person->prezime, person->godina);
    printf("****************************************\n");

    return 0;
}

Student* findByLastname(Student* head, char* prezime)
{
    Student* q;

    if (head->next == NULL) {
        printf("\nPrazna lista!\n");
        return head;
    }

    q = head->next;

    while (q != NULL && strcmp(q->prezime, prezime) != 0) {
        q = q->next;
    }

    if (q == NULL) {
        printf("\nElement nije pronaden!\n");
        return head;
    }

    else
        return q;
}

Student* delete(Student* head, Student* brisi)
{
    Student* prethodni = findPrevious(head, brisi);

    prethodni->next = brisi->next;

    free(brisi);

    return head;
}

Student* addBehind(Student* head, Student* iza)
{
    if (head->next == NULL) {
        return head;
    }

    Student* q;
    q = allocateNewStudent();

    printf("\nUnesite ime: ");
    scanf("%s", q->ime);
    printf("Unesite prezime: ");
    scanf("%s", q->prezime);
    printf("Unesite godinu rodenja: ");
    scanf(" %d", &q->godina);

    q->next = iza->next;
    iza->next = q;

    return head;
}

Student* addBefore(Student* head, Student* ispred)
{
    if (head->next == NULL) {
        return head;
    }

    Student* q;
    q = allocateNewStudent();
    Student* prethodni;
    prethodni = findPrevious(head, ispred);

    printf("\nUnesite ime: ");
    scanf("%s", q->ime);
    printf("Unesite prezime: ");
    scanf("%s", q->prezime);
    printf("Unesite godinu rodenja: ");
    scanf(" %d", &q->godina);

    q->next = prethodni->next;
    prethodni->next = q;

    return head;
}

int sort(Student* head)
{
    Student* ptr1;
    Student* lptr = NULL;
    int swapped;

    if (head->next == NULL)
        return 0;

    do {
        swapped = 0;
        ptr1 = head->next;

        while (ptr1->next != NULL && ptr1->next != lptr) {
            if (strcmp(ptr1->prezime, ptr1->next->prezime) > 0) {
                zamjena(head, ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    return 0;
}

int zamjena(Student* head, Student* prvi, Student* drugi)
{
    Student* temp = drugi->next;
    Student* prethodni = findPrevious(head, prvi);

    if (strcmp(prvi->prezime, drugi->prezime) == 0)
        return 0;

    else {
        prethodni->next = drugi;
        drugi->next = prvi;
        prvi->next = temp;
    }

    return 0;
}

Student* readFromFile(Student* head)
{
    FILE* fp = NULL;
    char* filename = (char*)malloc(sizeof(char) * WORD_LEN);
    Student* zadnji = findLast(head);

    printf("\nIme datoteke: ");
    scanf("%s", filename);
    if (strchr(filename, '.') == 0)
        strcat(filename, ".txt");

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("\nFATAL ERROR!\n%s se ne moze otvoriti!\n", filename);
        return head;
    }

    zadnji = fileToList(zadnji, fp);

    fclose(fp);
    return head;
}

Student* fileToList(Student* head, FILE* fp)
{
    char* line = (char*)malloc(sizeof(char) * 1024);
    char* buffer = (char*)malloc(sizeof(char) * 1024);
    int n;

    while (!feof(fp)) {
        Student* q = allocateNewStudent();
        fgets(buffer, 1024, fp);
        line = buffer;

        while (*line != 0) {
            sscanf(line, "%s %n", q->ime, &n);
            line += n;

            sscanf(line, "%s %n", q->prezime, &n);
            line += n;

            sscanf(line, " %d %n", &q->godina, &n);
            line += n;

            Student* last = findLast(head);
            last->next = q;
        }
    }

    return head;
}

int listToFile(Student* head)
{
    FILE* fp = NULL;
    char* filename = (char*)malloc(sizeof(char) * WORD_LEN);

    printf("\nUnesite ime datoteke: ");
    scanf("%s", filename);

    if (strchr(filename, '.') == 0)
        strcat(filename, ".txt");

    fp = fopen(filename, "w");

    if (fp == NULL) {
        printf("\nERROR! Datoteka %s nije otvorena!\n", filename);
        return 0;
    }

    if (head->next == NULL) {
        printf("\nERROR! Prazna lista!\n");
        return 0;
    }
    Student* q = head->next;

    fprintf(fp, "IME\t\t\t\tPREZIME\t\tGODINA RODENJA\n");

    while (q != NULL) {
        fprintf(fp, "%-16s%-16s%-4d\n", q->ime, q->prezime, q->godina);
        q = q->next;
    }

    return 0;
}