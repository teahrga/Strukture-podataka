#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>


#define MAX_NAME 128
#define MAX_LINE 128

typedef struct {
	char ime[MAX_NAME];
	char prezime[MAX_NAME];
	int broj_bodova;
}student;

int procitajStudente(char* imeDatoteke);
//student* ucitajStudente(char* imeDatoteke, int brStud);

int main()
{
	int brojStudenata = 0;
	student* stud = NULL;
	FILE* fp = NULL;
	double rel_bodovi;
	int i;
	

	brojStudenata = procitajStudente("stud.txt");
	printf("Broj studenata u datoteci je %d\n", brojStudenata);

	stud = (student*)malloc(brojStudenata * sizeof(student));
	if (stud == NULL)
	{
		printf("Neuspjesno alociranje memorije!\n");
		return -1;
	}

	fp = fopen("stud.txt", "r");
	if (fp == NULL) {
		printf("Neuspjesno otvaranje datoteke!\n");
		return 0;
	}

	for (i = 0; i < brojStudenata; i++)
	{
		fscanf(fp, " %s %s %d", stud[i].ime, stud[i].prezime, &stud[i].broj_bodova);
	}

	for (i = 0; i < brojStudenata; i++)
	{
		rel_bodovi = ((double)stud[i].broj_bodova /45) * 100;
		printf("%s %s %d %lf\n", stud[i].ime, stud[i].prezime, stud[i].broj_bodova, rel_bodovi);
		
	}
	fclose(fp);
	
	

	return 0;
}
int procitajStudente(char* imeDatoteke) {
	
	int br=0;
	FILE* fp = NULL;

	fp = fopen(imeDatoteke, "r");

	if (fp==NULL) {
		printf("Neuspjesno otvaranje datoteke!\n");
		return -1;
	}

	while (!feof(fp)) {
		char buffer[MAX_LINE] = { 0 };
		fgets(buffer, MAX_LINE, fp);
		br++;
	}
	fclose(fp);
	return br;
}
//student* ucitajStudente(char* imeDatoteke, int brStud) {
//	
//	student* studenti = NULL;
//	FILE* fp = NULL;
//	char buffer[MAX_LINE] = { 0 };
//	int br = 0;
//
//
//	
//
//	studenti = (student*)malloc(brStud * sizeof(student));
//	if (!studenti) {
//		printf("Neuspjesna alokacija memorije!\n");
//		return -1;
//	}
//	fp = fopen(imeDatoteke, "r");
//	if (fp==NULL) {
//		printf("Neuspjesno otvaranje datoteke!\n");
//		return 0;
//	}
//	while (!feof(fp)) {
//		fscanf(fp, " %s %s %lf\n", studenti[br].ime, studenti[br].prezime, &studenti[br].broj_bodova);
//		br++;
//	}
//	
//	fclose(fp);
//	return studenti;
//
//
//
//}
