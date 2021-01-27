#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define MAXSTRING 100
#define MAXNUMBER 15 // max phone number
#define MAXCONTACTS 1000
#define FILENAME "contacts.txt"

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
void printMenu();
void save();
void quit();
void menu();
void sortByLastName();
void sortByDate();

int compareNames(const void *pa, const void *pb);
void error(char message[]);
void success(char message[]);
void pause();
int getCurrentYear();
void printContacts(Contact arr[], int size);
bool validDate(char date[]);
bool validPhone(char num[]);
bool validEmail(char email[]);
bool compareDates(BirthDate date1, BirthDate date2);

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
        fscanf(f, "%99[^,],", contacts[Count].lastName);
        fscanf(f, "%99[^,],", contacts[Count].firstName);
        fscanf(f, "%2d-%2d-%4d,",
               &contacts[Count].date.day,
               &contacts[Count].date.month,
               &contacts[Count].date.year);
        fscanf(f, "%99[^,],", contacts[Count].address);
        fscanf(f, "%15[^,],", contacts[Count].number);
        fscanf(f, "%99s\n", contacts[Count].email);
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
        error("Person not found!\n");
    }
}

void add()
{
    char input[10];       // Stores input from the user
    char date[MAXSTRING]; // Stores the date tmp until it is valid
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
    } while (!validDate(date));

    do
    {
        printf("Enter phone number: ");
        scanf("%99s", contacts[Count].number);
    } while (!validPhone(contacts[Count].number));

    do
    {
        printf("Enter email: ");
        scanf("%100s", contacts[Count].email);
    } while (!validEmail(contacts[Count].email));

    Count++;

    success("\nContact added successfully.");

    printf("\nDo you want to add another one? (y/n) ");
    scanf("%s", input);

    if (strcmp(input, "y") != 0 && strcmp(input, "n") != 0)
        error("\nError! Unexpected input \n");

    if (strcmp(input, "y") == 0)
        add();
}

void deleteContact()
{
    // Contact hold[MAXCONTACTS];
    // char lastName[20], firstName[20];
    // int tmpCount;

    // printf("Enter the Last Name of the Contact to be deleted: ");
    // scanf("%s", lastName);
    // printf("Enter the First Name of the Contact to be deleted: ");
    // scanf("%s", firstName);
    // tmpCount = 0;
    // for (k = 0; k < Count; k++)
    // {
    //     int cmp1 = strcmp(contacts[k].lastName, lastName);
    //     int cmp2 = strcmp(contacts[k].firstName, firstName);
    //     if (cmp1 != 0 || cmp2 != 0)
    //     {
    //         hold[tmpCount] = contacts[k];
    //         tmpCount++;
    //     }
    // }
    // if (tmpCount != Count)
    // {

    //     for (j = 0; j < Count; j++)
    //     {
    //         strcpy(contacts[j].lastName, "\0");
    //         strcpy(contacts[j].firstName, "\0");
    //         contacts[j].date.day = 0;
    //         contacts[j].date.month = 0;
    //         contacts[j].date.year = 0;
    //         strcpy(contacts[j].address, "\0");
    //         strcpy(contacts[j].number, "\0");
    //         strcpy(contacts[j].email, "\0");
    //     }

    //     for (k = 0; k < tmpCount; k++)
    //         contacts[k] = hold[k];
    // }
    // else
    //     printf("\nDeleting a Contact not existing.\n");

    // success("\nContact(s) Deleted Successfully\n");
    // Count = tmpCount;

    // char lastName[MAXSTRING];
    // char firstName[MAXSTRING];

    // Contact newContacts[Count];
    // int newCount = 0;

    // printf("Enter the last name of the contact you want to delete: ");
    // scanf("%s", lastName);
    // printf("Enter the first name of the contact you want to delete: ");
    // scanf("%s", firstName);

    // for (i = 0; i < Count; i++)
    // {
    //     if ((strcmp(contacts[i].lastName, lastName) == 0) == 0 &&
    //         (strcmp(contacts[i].firstName, firstName) == 0) == 0)
    //     {
    //         newContacts[newCount] = contacts[i];
    //         newCount++;
    //     }
    // }
    // for (i = 0; i < newCount; i++)
    //     contacts[i] = newContacts[i];
    
    // Count = newCount;


    // for (i = 0; i < Count; i++)
    // {

    //     if ((strcmp(contacts[i].firstName, firstName) == 0) && (strcmp(contacts[i].lastName, lastName) == 0))
    //     {

    //         for (j = i; j < Count - 1; j++)
    //         {
    //             contacts[j] = contacts[j + 1];
    //         }
    //         Count--;

    //         printf("the contact is deleted successfully \n");
    //     }
    //     else
    //         printf("this name does not match any of the saved contacts\n");
    // }
}

void modify()
{
}

void printMenu()
{
    char input[10];
    char menuItems[3][MAXSTRING] = {"Normal", "Sort by last name.", "Sort by date of birth."};
    int menuSize = sizeof(menuItems) / sizeof(menuItems[0]);

    printf("Choose the number of your option:\n");
    for (i = 0; i < menuSize; i++)
        printf("(%d)  %s\n", (i + 1), menuItems[i]);
    scanf("%s", input);

    switch (atoi(input))
    {
    case 1:
        printContacts(contacts, Count);
        break;
    case 2:
        sortByLastName();
        break;
    case 3:
        sortByDate();
        break;

    default:
        error("\nError! Unexpected input. \n");
        pause();
        printMenu();
        break;
    }
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
    FILE *f;
    Contact tmpContacts[MAXCONTACTS];
    int tmpCount = 0;
    char input[10];
    bool flag = false;

    f = fopen(FILENAME, "r");

    while (!feof(f))
    { // %100[^,], Reads at most 100 character or until a comma is encountered
        fscanf(f, "%99[^,],", tmpContacts[tmpCount].lastName);
        fscanf(f, "%99[^,],", tmpContacts[tmpCount].firstName);
        fscanf(f, "%2d-%2d-%4d,",
               &tmpContacts[tmpCount].date.day,
               &tmpContacts[tmpCount].date.month,
               &tmpContacts[tmpCount].date.year);
        fscanf(f, "%99[^,],", tmpContacts[tmpCount].address);
        fscanf(f, "%15[^,],", tmpContacts[tmpCount].number);
        fscanf(f, "%99s\n", tmpContacts[tmpCount].email);
        tmpCount++;
    }
    fclose(f);

    if (tmpCount != Count)
        error("Warning: You have unsaved data that will be lost.\n");

    else if (tmpCount == Count)
    {
        for (i = 0; i < Count; i++)
        {
            // Compares contacts
            if (strcmp(contacts[i].firstName, tmpContacts[i].firstName) ||
                strcmp(contacts[i].lastName, tmpContacts[i].lastName) ||
                contacts[i].date.day != tmpContacts[i].date.day ||
                contacts[i].date.month != tmpContacts[i].date.month ||
                contacts[i].date.year != tmpContacts[i].date.year ||
                strcmp(contacts[i].address, tmpContacts[i].address) ||
                strcmp(contacts[i].number, tmpContacts[i].number) ||
                strcmp(contacts[i].email, tmpContacts[i].email))
            {
                flag = true;
                break;
            }
        }
        if (flag)
            error("Warning: You have unsaved data that will be lost.\n");
    }

    printf("Are you sure you want to quit? (y/n) ");
    scanf("%s", input);
    if (strcmp(input, "y") && strcmp(input, "n"))
    {
        error("\nError! Unexpected input.\n");
        pause();
    }

    if (strcmp(input, "y") == 0)
        exit(2);
}

// Utility functions
void menu()
{
    system("@cls||clear"); // clears the screen
    char input[10];
    char menuItems[8][MAXSTRING] = {"Query", "Add", "Delete", "Modify", "Print", "About", "Save", "Exit"};
    int menuSize = sizeof(menuItems) / sizeof(menuItems[0]);
    printf("\nChoose an option from the menu below (enter a number):\n");
    for (i = 0; i < menuSize; i++)
        printf("(%d)  %s\n", (i + 1), menuItems[i]);
    scanf("%s", input);

    switch (atoi(input))
    {
    case 1:
        printf("Query:\n");
        query();
        pause();
        break;
    case 2:
        printf("Add:\n");
        add();
        break;
    case 3:
        printf("Delete:\n");
        deleteContact();
        pause();
        break;
    case 4:
        printf("Modify:\n");
        modify();
        pause();
        break;
    case 5:
        printf("Print:\n");
        printMenu();
        pause();
        break;
    case 6:
        printf("\nMade with \u2764 by:\nHussein Mourad Kassem-6729\nAhmed Said Nouh-7086\nMohab Ayman abdelhamid-7127\nAbdelrahman Elsayed-3953\n");
        pause();
        break;
    case 7:
        save();
        pause();
        break;
    case 8:
        quit();
        break;
    default:
        error("Error! Unexpected input. \n");
        pause();
        break;
    }
}

void printContacts(Contact arr[], int size)
{
    printf("\n(Last,First,Date,Address,Number,Email)\n");

    for (i = 0; i < size; i++)
    {
        printf("%s,%s,%d-%d-%d,%s,%s,%s\n",
               arr[i].lastName,
               arr[i].firstName,
               arr[i].date.day,
               arr[i].date.month,
               arr[i].date.year,
               arr[i].address,
               arr[i].number,
               arr[i].email);
    }
}
int compareNames(const void *pa, const void *pb)
{
    const Contact *p1 = pa;
    const Contact *p2 = pb;
    return strcmp(p1->lastName, p2->lastName);
}
void sortByLastName()
{
    qsort(contacts, Count, sizeof(Contact), compareNames);
    printContacts(contacts, Count);
}

bool compareDates(BirthDate date1, BirthDate date2)
{
    // All cases when true should be returned
    if (date1.year > date2.year)
        return true;
    if (date1.year == date2.year && date1.month > date2.month)
        return true;
    if (date1.year == date2.year && date1.month == date2.month &&
        date1.day > date2.day)
        return true;
    // If none of the above cases satisfy, return false
    return false;
}

void sortByDate()
{

    for (i = 0; i < Count - 1; i++)
    {
        // Last i elements are already in place
        for (j = 0; j < Count - i - 1; j++)
        {
            if (compareDates(contacts[j].date, contacts[j + 1].date))
            {
                Contact temp;
                temp = contacts[j];
                contacts[j] = contacts[j + 1];
                contacts[j + 1] = temp;
            }
        }
    }

    printContacts(contacts, Count);
}

int getCurrentYear()
{
    time_t s;
    struct tm *currentTime;
    int CURRENTYEAR;
    s = time(NULL);
    currentTime = localtime(&s);
    CURRENTYEAR = currentTime->tm_year + 1900;
    return CURRENTYEAR;
}

bool validDate(char date[])
{
    long int dateLength = strlen(date); // stores the length of date
    int dashCount = 0;
    char *token;
    int day, month, year;

    if (dateLength < 8 || dateLength > 10)
    {
        error("Error! Invalid Date entry.\n");
        return false;
    }
    for (i = 0; i < dateLength; i++)
    {
        if (date[i] == '-')
            dashCount++;
    }

    if (dashCount != 2)
    {
        error("Invalid Date format!\n");
        return false;
    }

    token = strtok(date, "-");
    day = atoi(token);
    // Converts date as string to day, month , year as int
    for (i = 0; i <= 3; i++)
    {
        if (i == 1)
            month = atoi(token);
        else if (i == 2)
            year = atoi(token);
        token = strtok(NULL, "-");
    }

    if (day > 0 && day <= 31 && month > 0 && month <= 12 && year <= getCurrentYear() && year >= 1900)
    {
        // handles feb
        if (month == 2)
        {
            if (day > 29)
            {
                error("Error! Invalid Date entry.\n");
                return false;
            }
            else if (day == 29)
            {
                if (year % 4 != 0)
                {
                    error("Error! Invalid Date entry.\n");
                    return false;
                }
            }
        }
        //handle months which has only 30 days
        else if ((month == 4 || month == 6 ||
                  month == 9 || month == 11) &&
                 (day > 30))
        {
            error("Error! Invalid Date entry.\n");
            return false;
        }
    }
    else
    {
        error("Error! Invalid Date entry.\n");
        return false;
    }

    contacts[Count].date.day = day;
    contacts[Count].date.month = month;
    contacts[Count].date.year = year;
    return true;
}

bool validPhone(char num[])
{

    for (i = 0; i < strlen(num); i++)
    {
        if (!isdigit(num[i]) || strlen(num) < 7 || strlen(num) > 15)
        {
            error("Error! Invalid phone number.");
            printf(" (phone number must between 7 and 15 digits and doesn't contain characters)\n");
            return false;
        }
    }
    return true;
}

bool validEmail(char email[])
{
    int emailLength = strlen(email);
    for (i = 0; i <= emailLength; i++)
    {
        if (i != 0 && email[i] == '@' && i != emailLength - 1)
        {
            for (j = i; j <= emailLength; j++)
            {
                if (j != i && email[j] == '.' && j != emailLength - 1)
                    return true;
            }
        }
    }

    error("Error! Invalid email address.");
    printf(" (Email must contain @ sign and domain name)\n");
    return false;
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
