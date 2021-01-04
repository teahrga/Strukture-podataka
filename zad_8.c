#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define DIR_NAME_LENGHT (256)

typedef enum _insertResult {
	SUCCESS,
	ALLOCATION_FAILD,
	DUPLICATED_DIRECTORY,

}InsertResult;

struct dir;
typedef struct _dir* PositionDir;
typedef struct _dir {
	char name[DIR_NAME_LENGHT];
	PositionDir sibling;
	PositionDir child;
}Dir;

struct _stack;
typedef struct _stack* PositionStack;
typedef struct _stack {
	PositionDir dir;
	PositionStack next;
}Stack;

InsertResult md(PositionDir current, char* name);
PositionDir createDirectory(char* name);
PositionDir findDirectory(PositionDir current, char* name);
void pushDirectory(PositionStack stack, PositionDir dir);
PositionDir popDirectory(PositionStack stack);
void deleteTree(PositionDir current);


int main()
{
	PositionDir mainDir = NULL;
	Stack stack;
	PositionDir current = NULL;

	mainDir = createDirectory("C:");

	current = &mainDir;

	// dodati pozive funkcija
	deleteTree(mainDir);

	return EXIT_SUCCESS;
}

void pushDirectory(PositionStack stack, PositionDir dir) {
	PositionStack el = NULL;

	el = (PositionStack)malloc(sizeof(Stack));
	el->dir = dir;

	el->next = stack->next;
	stack->next = el;
}

PositionDir findDirectory(PositionDir current, char* name) {
	PositionDir child = current->child;

	while (child != NULL && strcmp(child->name, name) != 0) {
		child = child->sibling;
	}

	return child;
}

PositionDir popDirectory(PositionStack stack) {
	PositionDir result = NULL;
	PositionStack first = stack->next;

	if (NULL == first) return NULL;

	result = first->dir;

	stack->next = first->next;
	free(first);

	return result;
}

void deleteTree(PositionDir current) {
	if (current == NULL)return;
	deleteTree(current->sibling);
	deleteTree(current->child);
	free(current);
}

PositionDir createDirectory(char* name) {
	PositionDir dir = NULL;

	dir = (PositionDir)malloc(sizeof(Dir));

	if (NULL == dir) {
		printf("Memory allocation failed!\r\n");
		return NULL;
	}

	strcpy(dir->name, name);
	dir->sibling = NULL;
	dir->child = NULL;
}

InsertResult md(PositionDir current, char* name) {
	PositionDir el = NULL;
	PositionDir child = NULL;

	if (findDirectory(current, name) != NULL) {
		return DUPLICATED_DIRECTORY;
	}
	el = createDirectory(name);

	if (el == NULL) {
		return ALLOCATION_FAILD;
	}

	if (current->child == NULL) {
		current->child = el;
		return SUCCESS;
	}
	child = current->child;

	if (child == NULL){
		current->child = el;
		return SUCCESS;
	}

	if (strcmp(child->name, el->name) > 0) {
		current->child = el;
		el->sibling = child;
		return SUCCESS;
	}

	while (child->sibling != NULL && strcmp(child->sibling->name, el->name) < 0) {
		child = child->sibling;
	}

	el->sibling = child->sibling;
	child->sibling = el;
	return SUCCESS;
}
