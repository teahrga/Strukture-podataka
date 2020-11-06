#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 200

struct _student;
typedef struct _student* Position;
struct _student {
	char ime[MAX];
	char prezime[MAX];
	int godina_rodenja;
	Position Next;
};

void PrintList(Position);
void Insert(Position);
void InsertEnd(Position);
Position Find(Position);
Position FindPrev(Position);
void Delete(Position);
int main(void)
{
	struct _student Head;
	int opcija;
	Position stud_F = NULL;
	
	Head.Next = NULL;
	
	printf("Izaberite broj ispred naredbe koju zelite napraviti\n");
	printf("1) Unos elementa na pocetak liste\n");
	printf("2) Ispis elemenata liste\n");
	printf("3) Unos elementa na kraj liste\n");
	printf("4) Trazenje elementa u listi (po prezimenu)\n");
	printf("5) Brisanje elementa iz liste\n");

	scanf("%d", &opcija);

	switch (opcija)
	{
	case '1':
		Insert(&Head);
		break;
	case '2':
		PrintList(Head.Next);
		break;
	case '3':
		InsertEnd(&Head);
		break;
	case '4':
		stud_F = Find(&Head);
		if (stud_F != NULL)
			printf("Trazeni student je: %s %s %d", stud_F->ime, stud_F->prezime, stud_F->godina_rodenja);
		break;
	case '5':
		Delete(&Head);
		PrintList(Head.Next);
		break;
	default:
		printf("Unijeli ste nepodrzanu vrijednost!\n");
	}

	

	return 0;
}
void Insert(Position p)
{
	Position q;

	q = (Position)malloc(sizeof(struct _student));

	if (q == NULL)
		printf("Greska!Alokacija memorije nije uspjela.\n");
	else
	{
		printf("Unesite ime studenta:\n");
		scanf(" %s",q->ime);
		printf("Unesite prezime studenta:\n");
		scanf(" %s", q->prezime);
		printf("Unesite godinu rodenja studenta:\n");
		scanf("%d", q->godina_rodenja);

		q->Next = p->Next;
		p->Next = q;
	}
}
	
void PrintList(Position p)
{
	if (p == NULL)
		printf("Lista je prazna!");
	else
	{
		while (p != NULL)
		{
			printf(" %s %s %d", p->ime, p->prezime, p->godina_rodenja);
			p = p->Next;
		}
	}
}

void InsertEnd(Position p)
{
	while (p->Next != NULL)
		p = p->Next;

	Insert(p);
}

Position Find(Position p)
{
	char prez[MAX];

	printf("Unesite prezime po kojem zelite pretraziti listu:\n");
	scanf(" %s", prez);

	while (p->prezime != prez && p != NULL)
		p = p->Next;

	if (p->Next == NULL)
	{
		printf("Student se ne moze pronaci u listi!\n");
		return 0;
	}

	return p;
}

void Delete(Position p)
{
	
	Position prev;

	prev = FindPrev(p);

	if (prev != NULL)
	{
		p = prev->Next;
		prev->Next = p->Next;
		
		free(p);
	}
}

Position FindPrev(Position p)
{
	char prez[MAX];

	printf("Unesite prezime po kojem zelite pretraziti listu:\n");
	scanf(" %s", prez);

	while (p->Next != NULL && p->Next->prezime != prez)
		p = p->Next;

	if (p->Next == NULL)
	{
		printf("Student se ne moze pronaci u listi!\n");
		return 0;
	}

	return p;
}

