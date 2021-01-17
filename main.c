#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define MAXSTRING 100
#define MAXCONTACTS 1000
#define CURRENTYEAR 2021
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
void sortByLastName();
void sortByDate();
void error(char message[]);
void success(char message[]);
void clearScreen();
void pause();

int main()
{
    load();
    // add();

    while (true)
    {
        // if (isFuncRunning == false)
        menu();
    }
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
        fscanf(f, "%64d,", &contacts[Count].number);
        fscanf(f, "%s\n", contacts[Count].email);
        Count++;
    }
    fclose(f);
}

void printContacts()
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
    pause();
}

void menu()
{
    clearScreen();
    char input[10];
    char menuItems[8][MAXSTRING] = {"Query", "Add", "Delete", "Modify", "Print", "About", "Save", "Exit"};
    printf("\nChoose an item from the menu below:\n");
    for (i = 0; i < 8; i++)
        printf("(%d)  %s\n", (i + 1), menuItems[i]);
    scanf("%1s", input);

    if (atoi(input) == 0)
    {
        printf("Error! Unexpected input. ");
        pause();
    }

    switch (atoi(input))
    {
    case 1:
        query("Kassem");
        break;
    case 2:
        add();
        break;
    case 3:
        deleteContact();
        break;
    case 4:
        modify();
        break;
    case 5:
        printContacts();
        break;
    case 6:
        printf("Made with \u2764 by:\nHussein Mourad Kassem\nAhmed Said Nouh\n");
        exit(0);
        break;
    case 7:
        save();
        break;
    case 8:
        quit();
        break;
    default:
        printf("\nError! Unexpected input. \n");
        break;
    }
}

void query()
{
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
            printf("%d, ", contacts[i].number);
        }
    }
    pause();
}

void add()
{
    char date[12];
    printf("Enter Last Name: ");
    scanf("%99s", contacts[Count].lastName);
    printf("Enter First Name: ");
    scanf("%99s", contacts[Count].firstName);
    printf("Enter address: ");
    fgets(contacts[Count].address, MAXSTRING, stdin);
    scanf("%99[^\n]%*c", contacts[Count].address);
    do
    {
        printf("Enter Birth Day (dd-mm-yyyy): ");
        scanf("%99s", date);
        sscanf(date, "%2d-%2d-%4d",
               &contacts[Count].date.day,
               &contacts[Count].date.month,
               &contacts[Count].date.year);
        if (contacts[Count].date.day <=31 && contacts[Count.date.day] <=12 && contacts[Count].date.year <= CURRENTYEAR)
        {
            /* code */
        }
        

    } while (true);

    printf("Enter phone number: ");
    scanf("%64d", &contacts[Count].number);
    printf("Enter email: ");
    scanf("%100s", contacts[Count].email);
    Count++;
    // printContacts();
    success("\nContact successfully added");
    pause();
}

void deleteContact()
{
    int itemIndex;
    char searchTerm[MAXSTRING * 2];
    char firstName[MAXSTRING];
    char lastName[MAXSTRING];
    char *token;

    printf("Enter: ");
    fgets(searchTerm, MAXSTRING * 2, stdin);
    scanf("%99[^\n]%*c", contacts[Count].address);
    // printf("Enter the name of the person you want to delete: ");
    // fgets(searchTerm, MAXSTRING, stdin);
    // printf("%s\n", searchTerm);
    // token = strtok(searchTerm, " ");
    // printf("%s", token);
    // while (token != NULL)
    // {
    //     token = strtok(NULL, " ");
    //     printf("%s", token);
    // }

    // for (i = 0; i < Count; i++)
    // {
    //     if (strcmp(searchTerm, contacts[i].lastName) == 0)
    //     {
    //         printf("%s, ", contacts[i].lastName);
    //         printf("%s, ", contacts[i].firstName);
    //         printf("%d-%d-%d, ",
    //                contacts[i].date.day,
    //                contacts[i].date.month,
    //                contacts[i].date.year);
    //         printf("%s, ", contacts[i].address);
    //         printf("%d, ", contacts[i].number);
    //         printf("%s\n", contacts[i].email);
    //         itemIndex = i + 1;
    //     }
    // }
    // /* Copy next element value to current element */
    // for (i = index - 1; i < Count - 1; i++)
    //     contacts[i] = contacts[i + 1];

    // /* Decrement array size by 1 */
    // Count--;
    // success("Item deleted successfully");
}

void modify()
{
    error("TODO");
}

void save()
{
    FILE *f;
    f = fopen(FILENAME, "w");
    for (i = 0; i < Count; i++)
    {
        fprintf(f, "%s,%s,%d-%d-%d,%s,%d,%s\n",
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
    pause();
}
void quit()
{
    char input[1];
    error("warning: All unsaved data will be lost.\n");

    printf("Are you sure you want to quit? ('y' or 'n') ");
    scanf("%s", input);
    if (strcmp(input, "y") != 0 && strcmp(input, "n") != 0)
        printf("\nError! Unexpected input %s.\n", input);

    if (strcmp(input, "y") == 0)
        exit(2);
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
void pause()
{
    // char input[10];
    getchar();
    printf("\n\nPress Enter to Continue...");
    getchar();
    // puts("User pressed enter");
    // scanf("%[\n^\n]", input);
    // fgets(input, sizeof(input), stdin);
    // if()
}