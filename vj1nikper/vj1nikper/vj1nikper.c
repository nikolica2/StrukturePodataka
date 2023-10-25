/*1. Napisati program koji prvo pročita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamički alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i učitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE (128)
#define MAX_LINE (1024)
#define MAX_POINTS (15)

typedef struct _student
{
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	double points;
} student;

int readNoRowsInFile();
student* allocateMemoryAndReadStudents(int noStudents);
double calculateRelativePoints(double points);
int showStudents(int noStudents, student* students);

int main()
{
	int noRows = 0;
	student* students = NULL;

	noRows = readNoRowsInFile();
	if (noRows > 0)
	{
		students = allocateMemoryAndReadStudents(noRows);
		showStudents(noRows, students);

		free(students);
	}

	return 0;
}

int readNoRowsInFile()
{
	int counter = 0;
	FILE* filePointer = NULL;
	char buffer[MAX_SIZE] = { 0 };

	filePointer = fopen("students.txt", "r");
	if (!filePointer)
	{
		printf("Neuspjesno otvaranje datoteke!\n");
		return -1;
	}
	while (!feof(filePointer))
	{
		fgets(buffer, MAX_SIZE, filePointer);
		counter++;
	}

	fclose(filePointer);

	return counter;
}

student* allocateMemoryAndReadStudents(int noStudents)
{
	int counter = 0;
	FILE* filePointer = NULL;
	student* students = NULL;

	students = (student*)malloc(noStudents * sizeof(student));
	if (!students)
	{
		printf("Neuspjesna alokacija memorije!\n");
		return NULL;
	}

	filePointer = fopen("students.txt", "r");
	if (!filePointer)
	{
		printf("Neuspjesno otvaranje datoteke!\n");
		return NULL;
	}
	while (!feof(filePointer))
	{
		fscanf(filePointer, " %s %s %lf", students[counter].name, students[counter].surname, &students[counter].points);
		counter++;
	}

	fclose(filePointer);

	return students;
}

double calculateRelativePoints(double points)
{
	return ((points / MAX_POINTS) * 100);
}

int showStudents(int noStudents, student* students)
{
	int counter = 0;

	for (counter; counter < noStudents; counter++)
	{
		printf("Name: %s\t Surname: %s\t Absolute points: %.2lf\t Relative points: %.2lf%\t\n", students[counter].name,
			students[counter].surname, students[counter].points, calculateRelativePoints(students[counter].points));
	}

	return 0;
}
