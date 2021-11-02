#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 50

struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;
	Position next;
}Person;

int PrependList(Position head, char* name, char* surname, int birthYear);
int PrintList(Position first);
Position CreatePerson(Position head, char* name, char* surname, int birthYear);
int InsertAfter(Position position, Position newPerson);
Position FindLast(Position head);
Position FindBySurname(Position first, char* surname);
int AppendList(Position head, char* name, char* surname, int birthYear);
Position FindBefore(Position first);
int DeleteAfter(Position head, char* surname);

int main(int argc, char** argv)
{
	Person Head = { .next = NULL, .name = {0},
				  .surname = {0},.birthYear = 0 };
	Position p = &Head;

	return EXIT_SUCCESS;
}

int PrependList(Position head, char* name, char* surname, int birthYear) {

	Position newPerson = NULL;

	newPerson = CreatePerson(name, surname, birthYear);

	if (!newPerson) {
		return -1;
	}
	InsertAfter(head, newPerson);

	return EXIT_SUCCESS;
}
int PrintList(Position first) {
	
	Position temp = first;
	while (temp) {
		
		printf("Name: %s, Surname: %s, Birth Year: %d\n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;

	}
	return EXIT_SUCCESS;
}
Position CreatePerson(Position head, char* name, char* surname, int birthYear) {
	Position newPerson = NULL;

	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson) {
		perror("Can't allocate memory!\n");
		return NULL;
	}

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;

	newPerson->next = head->next;
	head->next = newPerson;

	return newPerson;
}
int InsertAfter(Position position, Position newPerson) {

	newPerson->next = position->next;
	position->next = NULL;
	return EXIT_SUCCESS;
}
Position FindLast(Position head) {

	Position temp = head;

	while (temp->next) {
		temp = temp->next;
	}
	return temp;
}
int AppendList(Position head, char* name, char* surname, int birthYear) {

	Position newPerson = NULL;
	Position last = NULL;

	newPerson = CreatePerson(name, surname, birthYear);

	if (!newPerson) {
		return -1;
	}

	last = FinfLast(head);
	InsertAfter(last, newPerson);

	return EXIT_SUCCESS;
}
Position FindBySurname(Position first, char* surname) {
	Position temp = first;

	while (temp) {
		if (strcmp(temp->surname, surname) == 0) {
			return temp;
		}

	}
}