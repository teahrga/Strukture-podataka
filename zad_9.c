#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

typedef struct _stablo {
    int element;

    struct _stablo* left;
    struct _stablo* right;
}Stablo;

int printMenu();
Stablo* Menu(Stablo*);
Stablo* insertNew(Stablo*, int);
int printTree(Stablo*);
Stablo* searchTree(Stablo*, int);
Stablo* deleteElement(Stablo*, Stablo*);
Stablo* findSmallest(Stablo*);

int main()
{
    Stablo* root = NULL;

    printMenu();

    do {
        root = Menu(root);
    } while (root);

    return 0;
}

int printMenu()
{
    printf("****************************************\n");
    printf("1) Unesite novi element\n");
    printf("2) Ispisite elemente iz stabla\n");
    printf("3) Pronadite element u stablu\n");
    printf("4) Izbrisite element iz stabla\n");
    printf("5) Ponovni ispis izbornika\n");
    printf("0) Izlaz iz programa\n");
    printf("****************************************\n");

    return 0;
}

Stablo* Menu(Stablo* root)
{
    int izbor, unesi, trazi, brisi;
    Stablo* element = (Stablo*)malloc(sizeof(Stablo));
    element->left = NULL;
    element->right = NULL;
    Stablo* del = (Stablo*)malloc(sizeof(Stablo));
    del->right = NULL;
    del->left = NULL;

    printf("\n--> ");
    scanf(" %d", &izbor);

    switch (izbor) {
    case 0:
        return NULL;
    case 1:
        printf("\nKoji element zelite unijeti u stablo? ");
        scanf(" %d", &unesi);
        root = insertNew(root, unesi);
        break;
    case 2:
        printf("\n");
        printTree(root);
        break;
    case 3:
        printf("\nKoji element zelite pronaci? ");
        scanf(" %d", &trazi);
        element = searchTree(root, trazi);
        if (element != NULL)
            printf("\nElement koji ste trazili | %d |\n", element->element);
        break;
    case 4:
        printf("\nKoji element zelite izbrisati? ");
        scanf(" %d", &brisi);
        del = searchTree(root, brisi);
        if (del == NULL)
            return root;
        root = deleteElement(root, del);
        break;
    case 5:
        printMenu();
        break;
    default:
        printf("\nKrivi unos! Pokusajte ponovo\n");
    }

    return root;
}

Stablo* insertNew(Stablo* root, int unesi)
{
    if (root == NULL) {
        root = (Stablo*)malloc(sizeof(Stablo));
        root->left = NULL;
        root->right = NULL;
        root->element = unesi;
    }

    else if (unesi > root->element) {
        root->right = insertNew(root->right, unesi);
    }
    else if (unesi < root->element) {
        root->left = insertNew(root->left, unesi);
    }

    return root;
}

int printTree(Stablo* root)
{
    if (root == NULL) {
        return 0;
    }

    printTree(root->left);
    printf(" %d", root->element);
    printTree(root->right);

    return 0;
}

Stablo* searchTree(Stablo* root, int broj)
{
    if (root == NULL) {
        printf("\nElement nije pronaden u stablu\n");
        return NULL;
    }

    else if (broj > root->element)
        return searchTree(root->right, broj);

    else if (broj < root->element)
        return searchTree(root->left, broj);

    else if (broj == root->element)
        return root;
}


Stablo* deleteElement(Stablo* root, Stablo* del)
{
    Stablo* pomocna = root;
    Stablo* temp = NULL;

    if (pomocna == NULL)
        return NULL;

    else if (pomocna->element > del->element)
        pomocna->left = deleteElement(pomocna->left, del);

    else if (pomocna->element < del->element)
        pomocna->right = deleteElement(pomocna->right, del);

    else if (pomocna->left && pomocna->right) {
        temp = findSmallest(pomocna->right);
        pomocna->element = temp->element;
        pomocna->right = deleteElement(pomocna->right, pomocna);
    }

    else {
        temp = pomocna;

        if (pomocna->left == NULL)
            pomocna = pomocna->right;
        else
            pomocna = pomocna->left;

        free(temp);
    }

    return pomocna;
}

Stablo* findSmallest(Stablo* root)
{
    if (root == NULL)
        return NULL;

    else if (root->left == NULL)
        return root;

    return findSmallest(root->left);
}