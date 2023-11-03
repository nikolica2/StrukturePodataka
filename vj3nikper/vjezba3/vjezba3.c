
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
3. Prethodnom zadatku dodati funkcije :
A.dinami?ki dodaje novi element iza odre?enog elementa,
B.dinami?ki dodaje novi element ispred odre?enog elementa,
C.sortira listu po prezimenima osoba,
D.upisuje listu u datoteku,
E.?ita listu iz datoteke.
*/

typedef struct person Person;
typedef Person* Position;

struct person {
    char name[50];
    char surname[50];
    int birth_year;
    Position position;
};

void add_first(Position head);
int print_list(Position temp);
void add_last(Position last);
void find_surname(Position temp);
void delete_element(Position temp);
void add_after(Position temp);
void add_before(Position temp);
void sort_by_surname(Position temp);
int add_to_file(Position temp);
int read_from_file();

int main() {

    Person head = { .name = {0}, .surname = {0}, .birth_year = {0} , .position = {NULL} };

    add_first(&head);
    add_first(&head);
    add_last(&head);
    print_list(&head);
    find_surname(&head);
    delete_element(&head);
    add_after(&head);
    add_before(&head);
    print_list(&head);
    //sort_by_surname(&head);
    add_to_file(&head);
    read_from_file();

    return 0;
};

void add_first(Position head) {
    Position new_element;
    new_element = (Position)malloc(sizeof(Person));
    printf("----DODAVANJE ELEMENTA NA PO?ETAK LISTE----\n");
    new_element->position = head->position;
    printf("insert name:");
    scanf("%s", new_element->name);
    printf("insert surname:");
    scanf("%s", new_element->surname);
    printf("insert godinu rodenja:");
    scanf("%d", &new_element->birth_year);

    head->position = new_element;
}
int print_list(Position temp) {
    printf("-----ISPIS LISTE-----\n");
    while (1) {
        temp = temp->position;
        printf("Name: %s\nSurname: %s\nYear of birth: %d\n\n", temp->name, temp->surname, temp->birth_year);
        if (temp->position == NULL) {
            return 0;
        }
    }

}
void add_last(Position last) {
    printf("----DODAVANJE ELEMENTA NA KRAJ LISTE----\n");
    while (last->position != NULL) {
        last = last->position;
    }
    Position new_element;
    new_element = (Position)malloc(sizeof(Person));

    new_element->position = last->position;
    printf("Insert name:");
    scanf("%s", new_element->name);
    printf("Insert surname:");
    scanf("%s", new_element->surname);
    printf("Insert birth year:");
    scanf("%d", &new_element->birth_year);
    last->position = new_element;

}
void find_surname(Position temp) {

    printf("\nInsert surname you want to find:");
    char wanted[50];
    scanf("%s", wanted);

    while (temp->position != NULL) {
        temp = temp->position;
        if (strcmp(temp->surname, wanted) == 0) {
            printf("Wanted element\nName: %s\nSurname: %s\nBirth year: %d\n", temp->name, temp->surname, temp->birth_year);
            break;
        }
        else if (temp->position == NULL) {
            printf("Element not found!\n");
        }
    }
}
void delete_element(Position temp) {
    Position previous = temp;
    Position wanted = temp;
    printf("-----DELETING WANTED ELEMENT-----\n");
    printf("Insert wanted name:");
    scanf("%s", wanted->name);
    printf("Insert wanted surname:");
    scanf("%s", wanted->surname);
    printf("Insert wanted year:");
    scanf("%d", &wanted->birth_year);
    while (temp->position != NULL) {
        temp = temp->position;
        if (strcmp(temp->surname, wanted->surname) == 0 && strcmp(temp->name, wanted->name) == 0 && temp->birth_year == wanted->birth_year) {
            break;
        }
        previous = previous->position;
    }
    if (previous->position != NULL) {
        previous->position = temp->position;
        free(temp);
    }
    else {
        printf("Element not found!\n");
    }
}
void add_after(Position temp) {
    Position new_element = (Position)malloc(sizeof(Person));
    Position wanted = temp;
    printf("----ADDING AFTER WANTED ELEMENT----\n");
    printf("Insert wanted name:");
    scanf("%s", wanted->name);
    printf("Insert wanted surname:");
    scanf("%s", wanted->surname);
    printf("Insert wanted year:");
    scanf("%d", &wanted->birth_year);
    while (temp->position != NULL) {
        temp = temp->position;
        if (strcmp(temp->surname, wanted->surname) == 0 && strcmp(temp->name, wanted->name) == 0 && temp->birth_year == wanted->birth_year) {
            break;
        }
        else if (temp->position == NULL) {
            printf("Element not found!");
        }
    }
    new_element->position = temp->position;
    temp->position = new_element;
    printf("\nInsert name of new element:");
    scanf("%s", new_element->name);
    printf("Insert surname:");
    scanf("%s", new_element->surname);
    printf("Insert birth year:");
    scanf("%d", &new_element->birth_year);

}
void add_before(Position temp) {
    Position new_element = (Position)malloc(sizeof(Person));
    Position wanted = temp;
    Position previous = temp;
    printf("----ADDING BEFORE WANTED ELEMENT----\n");
    printf("Insert wanted name:");
    scanf("%s", wanted->name);
    printf("Insert wanted surname:");
    scanf("%s", wanted->surname);
    printf("Insert wanted year:");
    scanf("%d", &wanted->birth_year);
    while (temp->position != NULL) {
        temp = temp->position;
        if (strcmp(temp->surname, wanted->surname) == 0 && strcmp(temp->name, wanted->name) == 0 && temp->birth_year == wanted->birth_year) {
            break;
        }
        else if (temp->position == NULL) {
            printf("Element not found!");
        }
        previous = previous->position;
    }
    new_element->position = previous->position;
    previous->position = new_element;
    printf("\nInsert name of new element:");
    scanf("%s", new_element->name);
    printf("Insert surname:");
    scanf("%s", new_element->surname);
    printf("Insert birth year:");
    scanf("%d", &new_element->birth_year);
}
void sort_by_surname(Position temp) {

}
int add_to_file(Position temp) {
    FILE* file_pointer;
    file_pointer = fopen("text.txt", "a");
    if (file_pointer == NULL) {
        puts("Pogreska!");
        return 1;
    }

    fprintf(file_pointer, "Name   Surname    Year of birth\n");
    while (1) {
        temp = temp->position;
        fprintf(file_pointer, "%s\t%s\t%d\n", temp->name, temp->surname, temp->birth_year);
        if (temp->position == NULL) {
            break;
        }
    }
    fclose(file_pointer);
    return 0;
}

int read_from_file() {
    Position temp = (Position)malloc(sizeof(Person));
    int number = -1, i = 0;
    FILE* file_pointer;
    file_pointer = fopen("text.txt", "r");
    if (file_pointer == NULL) {
        puts("Pogreska!");
        return 1;
    }
    while (!feof(file_pointer)) {
        char z = getc(file_pointer);
        if (z == '\n') {
            number++;
        }
    }
    fseek(file_pointer, 0, SEEK_SET);

    fscanf(file_pointer, "%*s %*s %*s %*s %*s");


    printf("-----STUDENTS IN FILE-----\n");
    for (i = 0; i < number; i++) {
        fscanf(file_pointer, "%s %s %d", temp->name, temp->surname, &temp->birth_year);
        printf("Name:%s\nSurname:%s\nYear of birth:%d\n\n", temp->name, temp->surname, temp->birth_year);
    }
    return 0;
}