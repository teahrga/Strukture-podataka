#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#define MAX 256
#define SIZE 11


typedef struct _student {
	char ime[MAX];
	char prezime[MAX];
	int br;
	struct _student* next;
}student;

student** Tablica(int);
int CitajizDatoteke(student**, char*);
int Unos(student** tablica, char*, char* last, int mbr);
student* NoviElement();
int IzracunTablice(char*, int);
int IspisTablice(student**, int);
int IspisListe(student*, int);
student* Sortirano(student*, char*, char*);
student* Rewind(student*, char*);
int IspisMbr(student* element);
student* Pronadi(student**, char*, char*);



int main()
{
	student** tablica;
	char ime[MAX] = { 0 };
	char prezime[MAX] = { 0 };
	char* filename;

	tablica = Tablica(SIZE);
	filename = (char*)malloc(sizeof(char) * MAX);

	printf("Kako se zove datoteka iz koje citate podatke?");
	scanf("%s", filename);
	if (strchr(filename, '.') == NULL)
		strcat(filename, ".txt");

	CitajizDatoteke(tablica, filename);
	IspisTablice(tablica, SIZE);

	printf("Unesite ime i prezime za ispis MBR-a [IME PREZIME]: ");
	scanf(" %s %s", ime, prezime);

	IspisMbr(Pronadi(tablica, ime, prezime));

	return 0;
}

student** Tablica(int b)
{
	int i = 0;
	student** tablica = malloc(b * sizeof(student*));

	if (tablica == NULL) {
		printf("Neuspješno alociranje memorije!");
		return NULL;
	}

	for (i = 0; i < b; i++) {
		tablica[i] = NoviElement();
	}

	return tablica;
}

int CitajizDatoteke(student** tablica, char* filename)
{
	char ime[MAX];
	char prezime[MAX];
	int br;
	char buffer[MAX] = { 0 };
	FILE* fp = fopen(filename, "r");

	if (fp == NULL)
		printf("Neuspješno alociranje memorije!");

	while (!feof(fp)) {
		fgets(buffer, MAX, fp);
		sscanf(buffer, "%s %s %d", ime, prezime, &br);
		Unos(tablica, ime, prezime, br);
	}

	fclose(fp);

	return 0;
}

int Unos(student** tablica, char* ime, char* prezime, int br)
{
	int pozicija = 0;
	student* element = NULL;
	student* pom = NULL;

	pozicija = IzracunTablice(prezime, SIZE);
	element = Sortirano(tablica[pozicija], ime, prezime);


	strcpy(element->ime, ime);
	strcpy(element->prezime, prezime);
	element->br = br;

	return 0;
}

int IzracunTablice(char* prezime, int br)
{
	int suma = 0;
	int i = 0;

	for (i = 0; i < 5; i++) {
		suma += (int)prezime[i];
	}

	return suma % br;
}

student* Sortirano(student* H, char* ime, char* prezime)
{
	student* element;
	student* pom = NULL;

	element = H;

	while (element->next && strcmp(prezime, element->next->prezime) > 0)
		element = element->next;

	if (element->next && !strcmp(prezime, element->next->prezime)) {
		element = Rewind(H, prezime);
		while (element->next && !strcmp(prezime, element->next->prezime) && strcmp(ime, element->next->ime) > 0)
			element = element->next;
	}
	pom = element->next;
	element->next = NoviElement();
	element = element->next;
	element->next = pom;

	return element;
}

student* Rewind(student* H, char* prezime)
{
	student* element = prezime;

	while (strcmp(element->next->prezime, prezime))
		element = element->next;

	return element;
}

student* NoviElement()
{
	student* element = malloc(sizeof(student));

	if (element == NULL) {
		printf("Neuspješno alociranje memorije!");
		return NULL;
	}

	memset(element->ime, 0, MAX);
	memset(element->prezime, 0, MAX);

	element->br = 0;
	element->next = NULL;

	return element;
}

int IspisTablice(student** tablica, int b)
{
	int i = 0;

	for (i = 0; i < b; i++)
		if (tablica[i]->next)
			IspisListe(tablica[i]->next, i);
		else
			printf("%d) --- \n", i);

	return 0;
}

int IspisListe(student* el, int i)
{
	student* element = el;

	printf("\n%d)", i);

	do {
		printf(" %s %s\t", element->ime, element->prezime);
		element = element->next;
	} while (element);

	return 0;
}

student* Pronadi(student** tablica, char* i, char* p)
{
	int x;

	x = IzracunTablice(p, SIZE);
	student* element = tablica[x]->next;

	while (element)
		if (!strcmp(element->prezime, p) && !strcmp(element->ime, i))
			return element;
		else
			element = element->next;

	return element;
}

int IspisMbr(student* el)
{
	if (el == NULL)
		printf("Unesen nepostojeci maticni broj!");
	return -1;

	printf("%d\n", el->br);

	return 0;
}