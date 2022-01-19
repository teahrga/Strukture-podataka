_CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> 
#include <time.h> 

; struct _Tree;
typedef struct _Tree* Node;
typedef struct _Tree {
    int value;
    Node left;
    Node right;
}
Tree;

struct _List;
typedef struct _List* Position;
typedef struct _List {
    int value;
    Position next;
}
List;

Position create_list_node(int value);
Position create_list_node(int value) {
    Position new_number = NULL;

    new_number = (Position)malloc(sizeof(List));
    new_number->next = NULL;
    new_number->value = value;

    return new_number;
}

Position find_last(Position head);
Position find_last(Position head) {
    Position temp = head;

    while (temp->next) {
        temp = temp->next;
    }

    return temp;
}

int insert_after(Position position, Position new_number);
int insert_after(Position position, Position new_number) {
    new_number->next = position->next;
    position->next = new_number;

    return 0;
}

int append_list(Position head, Position number);
int append_list(Position head, Position number) {
    Position last = NULL;

    if (!number) {
        return 1;
    }

    last = find_last(head);
    insert_after(last, number);

    return 0;
}

int print_to_list(Node position, Position head);
int print_to_list(Node position, Position head) {
    Position temp = NULL;

    if (position == NULL) {
        return 0;
    }

    print_to_list(position->left, head);
    temp = create_list_node(position->value);
    append_list(head, temp);
    print_to_list(position->right, head);

    return 0;
}

int print_list_to_file(Position position, char* filename);
int print_list_to_file(Position position, char* filename) {
    FILE* file = fopen(filename, "a");

    if (!file) {
        return 1;
    }

    while (position) {
        fprintf(file, "%d ", position->value);
        position = position->next;
    }

    fprintf(file, "\n");
    fclose(file);

    return 0;
}

int delete_after(Position position);
int delete_after(Position position) {
    Position deleted = NULL;

    if (position->next == NULL) {
        return 1;
    }

    deleted = position->next;
    position->next = deleted->next;

    free(deleted);
    return 0;
}

int delete_list(Position head);
int delete_list(Position head) {
    while (head->next) {
        delete_after(head);
    }

    return 0;
}

Node create_node(int value);
Node create_node(int value) {
    Node new_node = NULL;
    new_node = (Node)malloc(sizeof(Tree));

    if (!new_node) {
        return NULL;
    }

    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

Node insert_node(Node current, Node new_node);
Node insert_node(Node current, Node new_node) {
    if (!current) {
        return NULL;
    }

    if (new_node->value >= current->value) {
        if (!(current->left)) {
            current->left = new_node;
            return current;
        }
        insert_node(current->left, new_node);
        return current;
    }
    else {
        if (!(current->right)) {
            current->right = new_node;
            return current;
        }
        insert_node(current->right, new_node);
        return current;
    }

    return current;
}

int print_in_order(Node position);
int print_in_order(Node position) {
    if (position == NULL) {
        return 0;
    }

    print_in_order(position->left);
    printf("%d ", position->value);
    print_in_order(position->right);

    return 0;
}

int replace(Node current);
int replace(Node current) {
    int left = 0;
    int right = 0;
    if (current == NULL)
        return 0;

    if (!current->left && !current->right);
    else if (!current->left) right = current->right->value;
    else if (!current->right) left = current->left->value;
    else {
        left = current->left->value;
        right = current->right->value;
    }

    current->value = left + right + replace(current->left) + replace(current->right);

    return current->value;
}

int fill_tree_random(Node root, int amount);
int fill_tree_random(Node root, int amount) {
    Node temp = NULL;

    if (!root) {
        return 1;
    }

    // seed
    srand(time(0));
    for (int i = 0; i < amount; i++) {
        temp = create_node(rand() % 79 + 11);
        insert_node(root, temp);
    }

    return 0;
}

int main() {
    Node root = NULL;
    Node node = NULL;
    Node temp = NULL;
    Position head = NULL;

    root = (Node)malloc(sizeof(Tree));
    root->value = INT_MAX;
    root->left = NULL;
    root->right = NULL;

    head = (Position)malloc(sizeof(List));
    head->value = 0;
    head->next = NULL;

    fill_tree_random(root, 10);
    print_in_order(root->right);
    printf("\n");

    replace(root->right);
    print_in_order(root->right);

    return 0;
}