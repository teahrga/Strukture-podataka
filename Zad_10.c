#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

#define LINE_LEN 1024
#define WORD_LEN 55

typedef struct _stablo {
    char element[LINE_LEN];

    struct _stablo* left;
    struct _stablo* right;
}Stablo;

typedef struct _stog {
    char element[LINE_LEN];

    struct _stog* next;
}Stog;

int readFile(Stog*);
int loadPostfix(Stog*, char*);
int Push(Stog*, char*);
char* Pop(Stog*);
Stablo* stogToTree(Stog*, Stablo*);
Stablo* create();
int isOperand(char);
int print(Stablo*);

int main()
{
    Stog* head = (Stog*)malloc(sizeof(Stog));
    head->next = NULL;
    Stablo* root = NULL;

    readFile(head);
    root = stogToTree(head, root);
    print(root);

    return 0;
}

int readFile(Stog* head)
{
    FILE* fp = NULL;
    char* filename = (char*)malloc(sizeof(char) * WORD_LEN);

    printf("Koju datoteku zelite otvoriti?\n");
    scanf("%s", filename);

    if (strchr(filename, '.') == 0)
        strcat(filename, ".txt");

    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("\nERROR! File could not open!");
        return -1;
    }

    char* line = (char*)malloc(sizeof(char) * LINE_LEN);

    fgets(line, LINE_LEN, fp);

    loadPostfix(head, line);

    return 0;
}

int loadPostfix(Stog* head, char* line)
{
    int n;
    char* znak = (char*)malloc(sizeof(char) * LINE_LEN);

    while (sscanf(line, "%s %n", &n, znak) == 1) {
        Push(head, znak);
        line += n;
        n = 0;
    }

    return 0;
}

int Push(Stog* head, char* znak)
{
    Stog* p = (Stog*)malloc(sizeof(Stog));

    if (p == NULL)
        return -1;

    p->next = head->next;
    head->next = p;
    strcpy(p->element, znak);

    return 0;
}

char* Pop(Stog* head)
{
    Stog* pomocni = (Stog*)malloc(sizeof(Stog));
    char* temp = (char*)malloc(sizeof(char) * LINE_LEN);

    if (head->next == NULL || pomocni == NULL || temp == NULL) {
        printf("\nERROR!");
        return NULL;
    }

    pomocni = head->next;
    strcpy(temp, pomocni->element);
    head->next = pomocni->next;
    free(pomocni);

    return temp;
}

Stablo* stogToTree(Stog* head, Stablo* root)
{
    char* string;

    string = Pop(head);

    root = create();

    strcpy(root->element, string);

    if (isOperand(root->element[0])) {
        root->right = stogToTree(head, root->right);
        root->left = stogToTree(head, root->left);
    }

    return root;
}

Stablo* create()
{
    Stablo* new = (Stablo*)malloc(sizeof(Stablo));
    new->left = NULL;
    new->right = NULL;

    return new;
}

int isOperand(char simbol)
{
    if (simbol == '+')
        return 1;

    else if (simbol == '-')
        return 1;

    else if (simbol == '*')
        return 1;

    else if (simbol == '/')
        return 1;

    return 0;
}

int print(Stablo* root)
{
    if (!root)
        return 0;

    printf("(");
    print(root->left);
    printf("%s", root->element);
    print(root->right);
    printf(")");

    return 0;
}