#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

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

// Global Variables:
// Stores the contacts
Contact contacts[MAXCONTACTS];
// Stores the number of contacts
int Count = 0;
// Used for iteration
int i = 0;
int j = 0;
// Used to render menu
bool isFuncRunning = false;

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

// Utility functions
void sortByLastName();
void sortByDate();
void error(char message[]);
void success(char message[]);
void clearScreen();

int main()
{
    error("TODO");
}

void load()
{
    //! TODO
}

void printContacts()
{
    //! TODO
}

void menu()
{

    //! TODO
}

void query()
{
    //! TODO
}

void add()
{
    //! TODO
}

void deleteContact()
{
    //! TODO
}

void modify()
{
    //! TODO
}

void save()
{
    //! TODO
}
void quit()
{
    //! TODO
}

// Utility functions
void sortByLastName()
{
    //! TODO
}
void sortByDate()
{
    //! TODO
}
void error(char message[])
{
    printf("\033[1;31m%s\033[0m", message);
}
void success(char message[])
{
    printf("\033[0;32m%s\033[0m", message);
}
void clearScreen()
{
    system("@cls||clear");
}

//! TODO REPORT