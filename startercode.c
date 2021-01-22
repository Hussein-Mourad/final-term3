#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define MAXSTRING 100
#define MAXNUMBER 15 // max phone number
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
    char number[MAXNUMBER];
    char email[MAXSTRING];

} Contact;

// Prototypes
void load();
void query();
void add();
void deleteContact();
void modify();
void printContacts();
void save();
void quit();
void menu();
void sortByLastName();
void sortByDate();
void error(char message[]);
void success(char message[]);
void pause();

// Global Variables:
// Stores the contacts
Contact contacts[MAXCONTACTS];
// Stores the number of contacts
int Count = 0;
// Used for iteration
int i = 0;
int j = 0;
int k = 0;

int main()
{
    load();
    while (true)
        menu();
}

void load()
{
    FILE *f;
    f = fopen(FILENAME, "r");
    if (f == NULL)
    {
        error("Error! Invalid filename\n");
        exit(1);
    }

    while (!feof(f))
    { // %100[^,], Reads at most 100 character or until a comma is encountered
        fscanf(f, "%100[^,],", contacts[Count].lastName);
        fscanf(f, "%100[^,],", contacts[Count].firstName);
        fscanf(f, "%2d-%2d-%4d,",
               &contacts[Count].date.day,
               &contacts[Count].date.month,
               &contacts[Count].date.year);
        fscanf(f, "%100[^,],", contacts[Count].address);
        fscanf(f, "%15s,", contacts[Count].number);
        fscanf(f, "%s\n", contacts[Count].email);
        Count++;
    }
    fclose(f);
}

void query()
{
    bool found = false;
    char searchTerm[MAXSTRING];
    printf("Enter the last name of the person: ");
    scanf("%s", searchTerm);

    for (i = 0; i < Count; i++)
    {
        if (strcmp(searchTerm, contacts[i].lastName) == 0)
        {
            printf("%s, ", contacts[i].lastName);
            printf("%s, ", contacts[i].firstName);
            printf("%d-%d-%d, ",
                   contacts[i].date.day,
                   contacts[i].date.month,
                   contacts[i].date.year);
            printf("%s, ", contacts[i].address);
            printf("%s, ", contacts[i].number);
            printf("%s\n", contacts[i].email);
            found = true;
        }
    }
    if (!found)
    {
        printf("No person found! \n");
    }
}

void add()
{
    error("TODO\n");
}

void deleteContact()
{
    error("TODO\n");
}

void modify()
{
    error("TODO\n");
}

void printContacts()
{
    error("TODO\n");
}

void save()
{
    FILE *f;
    f = fopen(FILENAME, "w");
    for (i = 0; i < Count; i++)
    {
        fprintf(f, "%s,%s,%d-%d-%d,%s,%s,%s\n",
                contacts[i].lastName,
                contacts[i].firstName,
                contacts[i].date.day,
                contacts[i].date.month,
                contacts[i].date.year,
                contacts[i].address,
                contacts[i].number,
                contacts[i].email);
    }
    fclose(f);
    success("\nContacts saved successfully");
}

void quit()
{
    char input[1];
    error("warning: All unsaved data will be lost.\n");

    printf("Are you sure you want to quit? (y/n) ");
    scanf("%s", input);
    if (strcmp(input, "y") != 0 && strcmp(input, "n") != 0)
        printf("\nError! Unexpected input %s.\n", input);

    if (strcmp(input, "y") == 0)
        exit(2);
}

// Utility functions
void menu()
{
    system("@cls||clear"); // clears the screen
    char input[10];
    char menuItems[8][MAXSTRING] = {"Query", "Add", "Delete", "Modify", "Print", "About", "Save", "Exit"};
    printf("\nChoose an item from the menu below:\n");
    for (i = 0; i < 8; i++)
        printf("(%d)  %s\n", (i + 1), menuItems[i]);
    scanf("%s", input);

    if (atoi(input) == 0)
    {
        printf("Error! Unexpected input. ");
        pause();
    }

    switch (atoi(input))
    {
    case 1:
        query("Kassem");
        pause();
        break;
    case 2:
        add();
        pause();
        break;
    case 3:
        deleteContact();
        pause();
        break;
    case 4:
        modify();
        pause();
        break;
    case 5:
        printContacts();
        pause();
        break;
    case 6:
        error("TODO\n");
        pause();
        break;
    case 7:
        save();
        pause();
        break;
    case 8:
        quit();
        pause();
        break;
    default:
        printf("\nError! Unexpected input. \n");
        pause();
        break;
    }
}

void sortByLastName()
{
    error("TODO\n");
}

void sortByDate()
{
    error("TODO\n");
}

void error(char message[])
{
    printf("\033[1;31m%s\033[0m", message);
}

void success(char message[])
{
    printf("\033[0;32m%s\033[0m", message);
}

void pause()
{
    getchar();
    printf("\nPress Enter to Continue...");
    getchar();
}
