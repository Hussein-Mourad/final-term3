#include <stdio.h>
#include <stdlib.h>
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

// Global Variables
Contact contacts[MAXCONTACTS];
int Count = 0;
int i = 0;

// Prototypes
void load();
void query();
void add();
void delete ();
void modify();
void print();
void save();
void quit();
void error(char message[]);
void succuss(char message[]);
void clearScreen();

int main()
{
    load();
    add();
}

void load()
{
    FILE *f;
    f = fopen(FILENAME, "r");
    if (f == NULL)
    {
        printf("Error! Invalid filename\n");
        // error("Error! Invalid filename\n");
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
        fscanf(f, "%64d,", &contacts[Count].number);
        fscanf(f, "%s\n", contacts[Count].email);
        Count++;
    }
    fclose(f);
}

void print()
{
    printf("Last, First, Date, Address, Number, Email\n");
    for (i = 0; i < Count; i++)
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
    }
}

void query(char s[])
{
    for (i = 0; i < Count; i++)
    {
        if (strcmp(s, contacts[i].lastName) == 0)
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
        }
    }
}

void add()
{
    char tmp[11];
    Count++;
    printf("Enter Last Name: ");
    scanf("%s", contacts[Count].lastName);
    printf("Enter First Name: ");
    scanf("%s", contacts[Count].firstName);
    // printf("Enter Birth Day(separated by - ): ");
    // scanf("%s",
    //       tmp);
    // sscanf(tmp, "%d-%d-%d",
    //        &contacts[Count].date.day,
    //        &contacts[Count].date.month,
    //        &contacts[Count].date.year);
    printf("Enter address: ");
    fgets(contacts[Count].address, MAXSTRING, stdin);
    // scanf("%[^\n]%*c", contacts[Count].address);
    printf("Enter phone number: ");
    scanf("%d", &contacts[Count].number);
    printf("Enter email: ");
    scanf("%s", contacts[Count].email);

    printf("%s, ", contacts[Count].lastName);
    printf("%s, ", contacts[Count].firstName);
    printf("%d-%d-%d, ",
           contacts[Count].date.day,
           contacts[Count].date.month,
           contacts[Count].date.year);
    printf("%s, ", contacts[Count].address);
    printf("%d, ", contacts[Count].number);
    printf("%s\n", contacts[Count].email);
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