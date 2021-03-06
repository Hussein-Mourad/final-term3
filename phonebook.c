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

void error(char message[]);
void success(char message[]);
void pause();
int getCurrentYear();
void printContacts(Contact arr[], int size);
void printOneContact(Contact arr[], int index);
void modifyContact(int index);
bool validDate(char date[], int count);
bool validPhone(char num[]);
bool validEmail(char email[]);
int compareNames(const void *pa, const void *pb);
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
            printOneContact(contacts, i);
            found = true;
        }
    }
    if (!found)
        error("Person not found!\n");
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

    } while (!validDate(date, Count));

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
    char lastName[MAXSTRING];
    char firstName[MAXSTRING];

    Contact newContacts[Count];
    Contact deletedContacts[Count];
    int deletedCount = 0;
    int newCount = 0;
    printf("Enter the last name of the contact you want to delete: ");
    scanf("%s", lastName);
    printf("Enter the first name of the contact you want to delete: ");
    scanf("%s", firstName);

    // copies all contacts into new array
    for (i = 0; i < Count; i++)
    {
        if (strcmp(contacts[i].lastName, lastName) ||
            strcmp(contacts[i].firstName, firstName))
        {
            newContacts[newCount] = contacts[i];
            newCount++;
        }
        else
        {
            deletedContacts[deletedCount] = contacts[i];
            deletedCount++;
        }
    }

    if (newCount != Count)
    {
        for (i = 0; i < Count; i++)
            contacts[i] = newContacts[i];
        Count = newCount;

        printf("\nDeleted Contacts: ");
        printContacts(deletedContacts, deletedCount);
        success("Contacts deleted successfully.\n");
    }
    else
        error("\nError! contact not found.");
}

void modify()
{
    int items[MAXCONTACTS];
    int itemsCount = 0; // Stores index
    char lastName[MAXSTRING];
    char input[10];

    printf("Enter the last name of the person: ");
    scanf("%99s", lastName);

    for (i = 0; i < Count; i++)
    {
        if (strcmp(lastName, contacts[i].lastName) == 0)
        {
            items[itemsCount] = i;
            itemsCount++;
        }
    }

    // handles input from the user and modifies the contact
    if (itemsCount == 1)
        modifyContact(items[0]);
    else if (itemsCount > 1)
    {
        printf("\nChoose an item to delete (Enter a number):\n");
        for (i = 0; i < itemsCount; i++)
            printf("(%d) %s,%s,%d-%d-%d,%s,%s,%s\n",
                   (i + 1),
                   contacts[items[i]].lastName,
                   contacts[items[i]].firstName,
                   contacts[items[i]].date.day,
                   contacts[items[i]].date.month,
                   contacts[items[i]].date.year,
                   contacts[items[i]].address,
                   contacts[items[i]].number,
                   contacts[items[i]].email);

        scanf("%s", input);

        int num = atoi(input);

        if (num == 0 || num > itemsCount + 1)
        {
            printf("Error! Unexpected input. ");
            pause();
        }
        // handles input from the user and modifies the contact
        modifyContact(items[num - 1]);
    }
    else
        error("Error! Contact not found.\n");
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
        exit(0);
}

// Utility functions
void menu()
{
    system("@cls||clear"); // clears the screen
    char input[10];
    char menuItems[8][MAXSTRING] = {"Query", "Add", "Delete", "Modify", "Print", "About", "Save", "Quit"};
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

void modifyContact(int index)
{
    char date[MAXSTRING];
    printf("Contact to be modified: ");
    printOneContact(contacts, index);
    printf("Enter new last name: ");
    scanf("%99s", contacts[index].lastName);
    printf("Enter new first name: ");
    scanf("%99s", contacts[index].firstName);
    printf("Enter new address: ");
    fgets(contacts[index].address, MAXSTRING, stdin);
    scanf("%99[^\n]%*c", contacts[index].address);

    do
    {
        printf("Enter Birth Day (dd-mm-yyyy): ");
        scanf("%99s", date);
    } while (!validDate(date, index));

    do
    {
        printf("Enter new phone number: ");
        scanf("%99s", contacts[index].number);
    } while (!validPhone(contacts[index].number));

    do
    {
        printf("Enter new email: ");
        scanf("%99s", contacts[index].email);

    } while (!validEmail(contacts[index].email));
    success("Contact modified successfully\n");
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
void printOneContact(Contact arr[], int index)
{
    printf("%s,%s,%d-%d-%d,%s,%s,%s\n",
           arr[index].lastName,
           arr[index].firstName,
           arr[index].date.day,
           arr[index].date.month,
           arr[index].date.year,
           arr[index].address,
           arr[index].number,
           arr[index].email);
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

bool validDate(char date[], int count)
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

    contacts[count].date.day = day;
    contacts[count].date.month = month;
    contacts[count].date.year = year;

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
