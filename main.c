#include <stdio.h>
#include <stdlib.h>

#define MAXSTRING 100
#define MAXCONTACTS 1000
#define FILENAME "phonfebook.txt"

// Structures
typedef struct BirthDate
{
    int day;
    int month;
    int year;
} BirthDate;

typedef struct Contact
{
    char firstName[MAXSTRING];
    char lastName[MAXSTRING];
    BirthDate date;
    char address[MAXSTRING];
    int number;
    char email[MAXSTRING];

} Contact;

// Global Variables
Contact contacts[MAXCONTACTS];
int contactCount = 0;

// Prototypes
void load();
void query();
void add();
void delete ();
void modify();
void print();
void save();
void quit();
void red();
void green();
void reset();

void clearScreen()
{
    system("@cls||clear");
}

int main()
{
    load();
    print();
}
void red()
{
    printf("\033[1;31m");
}

void green()
{
    printf("\033[0;32m");
}

void reset()
{
    printf("\033[0m");
}

void load()
{
    FILE *f;
    f = fopen(FILENAME, "r");
    if (f == NULL)
    {
        void red();
        printf("Error! Invalid filename\n");
        void reset();
        void green();
        printf("Error! Invalid filename\n");
        void reset();
        exit(1);
    }

    while (!feof(f))
    { // %100[^,], Reads at most 100 character or until a comma is encountered
        fscanf(f, "%100[^,],", contacts[contactCount].lastName);
        fscanf(f, "%100[^,],", contacts[contactCount].firstName);
        fscanf(f, "%2d-%2d-%4d,",
               &contacts[contactCount].date.day,
               &contacts[contactCount].date.month,
               &contacts[contactCount].date.year);
        fscanf(f, "%100[^,],", contacts[contactCount].address);
        fscanf(f, "%64d,", &contacts[contactCount].number);
        fscanf(f, "%s\n", contacts[contactCount].email);
        contactCount++;
    }
    fclose(f);
}

void print()
{
    printf("Last, First, Date, Address, Number, Email\n");
    for (int i = 0; i < contactCount; i++)
    {
        printf("%s, ", contacts[i].lastName);
        printf("%s, ", contacts[i].firstName);
        printf("%d-%d-%d, ",
               contacts[i].date.day,
               contacts[i].date.month,
               contacts[i].date.year);
        printf("%s, ", contacts[i].address);
        printf("%d, ", contacts[i].number);
        printf("%s\n", contacts[i].email);
        if (i < 4)
            clearScreen();
    }
}

