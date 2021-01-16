#include <stdio.h>
#include <stdlib.h>

#define MAXSTRING 100
#define MAXCONTACTS 1000
#define FILENAME "phonebook.txt"

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

int main()
{
    load();
    print();
}

void load()
{
    FILE *f;
    f = fopen(FILENAME, "r");
    if (f == NULL)
    {
        printf("Error! Invalid filename");
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
    printf("| Last Name |\tFirst Name |\tDate |\tAddress |\tNumber |\tEmail |\n");
    for (int i = 0; i < contactCount; i++)
    {
        printf("%s\r", contacts[i].lastName);
        printf("%s\r", contacts[i].firstName);
        printf("%d-%d-%d\r",
               contacts[i].date.day,
               contacts[i].date.month,
               contacts[i].date.year);
        printf("%s\r", contacts[i].address);
        printf("%d\r", contacts[i].number);
        printf("%s\r", contacts[i].email);
    }
}