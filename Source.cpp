#include<stdio.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX 50

typedef struct {

	char ime[MAX];
	char prezime[MAX];
	int bodovi;
}_student;

int BrojRedaka(FILE*);
int main()
{
	_student* stud;
	FILE* ulz;
	int br_red = 0;
	int i = 0;
	float rel_bod;

	ulz = fopen("lista.txt", "r");

	if (ulz == NULL)
		printf("Greska pri otvaranju datoteke!");



	br_red = BrojRedaka(ulz);
	//while(!feof(ulz))
	//  if(fgetc(ulz)=='\n') br_bod++;
	stud = (_student*)malloc(br_red * sizeof(_student));

	for (i = 0; i < br_red; i++)
	{
		fscanf(ulz, "%s %s %d", stud[i].ime, stud[i].prezime, &stud[i].bodovi);
	}

	for (i = 0; i < br_red; i++)
	{
		rel_bod = (float)stud[i].bodovi / 20 * 100;
		printf("%s %s %d %f", stud[i].ime, stud[i].prezime, stud[i].bodovi, rel_bod);
	}

	return 0;
}
int BrojRedaka(FILE* dat)
{

	char buff[1000];
	int n = 0;

	while (!feof(dat))
	{
		fgets(buff, sizeof(buff), dat);
		n++;
	}
	return n;
}
