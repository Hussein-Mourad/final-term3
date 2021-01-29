# Phone Book App

## Contents:

- [Phone Book App](#phone-book-app)
  - [Contents:](#contents)
  - [User Guide](#user-guide)
    - [Starting the program](#starting-the-program)
    - [Navigation](#navigation)
    - [Query](#query)
    - [Add](#add)
    - [Delete](#delete)
    - [Modify](#modify)
    - [Print](#print)
    - [About](#about)
    - [Save](#save)
    - [Quit](#quit)
  - [How it Works](#how-it-works)
    - [Main](#main)
      - [Code:](#code)
    - [Structs and Global variables:](#structs-and-global-variables)
    - [Menu](#menu)
      - [Code:](#code-1)
      - [Sample Runs:](#sample-runs)
    - [Load](#load)
      - [Code:](#code-2)
    - [Query](#query-1)
      - [Code:](#code-3)
      - [Sample Run:](#sample-run)
    - [Add](#add-1)
      - [Code:](#code-4)
      - [Sample Runs:](#sample-runs-1)
    - [Delete](#delete-1)
      - [Code:](#code-5)
      - [Sample Runs:](#sample-runs-2)
    - [Modify](#modify-1)
    - [Print](#print-1)
      - [Code:](#code-6)
      - [Sample Run:](#sample-run-1)



## User Guide

### Starting the program 
You can start the program by double clicking on the program icon or by entering  `./phonebook.exe` in the cmd or powershell if you are on windows or entering `./phonebook` in the terminal if you are on linux or mac

### Navigation
When you start the program you get a menu which helps in navigating the program. You need to enter the number corresponding to the option you want to choose for example if you enter the number 1 then you choose the Query option.

### Query
You need to enter the last name of the person you are searching for and the program will show all contacts matching that name.

### Add
You need to enter the last name, first name, birth date formatted as (dd-mm-yyyy), address, phone number, and the email of the contact you want to add. You need to enter valid input as the program will keep asking for input until you enter a valid one.

### Delete
You need to enter the last name then the first name of the contact you want to delete and the program will delete all contacts matching that name.

### Modify 
You need to enter the last name of the contact you want to modify. In case that there are multiple contacts will the same last name you are prompted to choose one of them from a menu by entering the number corresponding to the contact then you need to enter the new information of the contact. You need to enter valid input as the program will keep asking for input until you enter a valid one.

### Print
You need to choose how the contacts are printed whether printed normally, sorted by last name, or sorted by date of birth. You can choose by entering the number corresponding to the option you want to choose. then the program prints all the contacts you have at the moment. If you saved after printing then the contacts' sort state is saved.

### About
This option prints the name and the id of all contributors to this software.

### Save
This option saves the contacts to the phone-book.

### Quit
This option exits the program and warns the user if he has unsaved data so his data won't be lost.

<hr/>

## How it Works
This section is going to demonstrate the functionality of the program starting with the required functionality and then going through extra ones. First we need to start by the driver code

### Main 
In the main function we start by calling `load()` which load the contact to memory and then calls `menu()` which runs inside a while loop at it handles the rest of the program until the user chooses to exit


#### Code:
```C
int main()
{
    load();
    while (true)
        menu();
}
```

### Structs and Global variables:

```C
// Constants
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
// Global Variables:
// Stores the contacts
Contact contacts[MAXCONTACTS];
// Stores the number of contacts
int Count = 0;
// Used for iteration
int i = 0;
int j = 0;
int k = 0;
```

### Menu
This is the most important function as it helps the user navigate through the program with ease. It starts of by clearing the screen and then it renders a menu where the user can choose from several options. It also Checks for invalid input.

#### Code:
```C
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
```
#### Sample Runs:
![code-run](img/menu1.png "Code Run")

**Error Handling**

![code-run](img/menu2.png "Code Run")

### Load
This functions reads all the contacts from a file and stores them in a global array of type Contact. 
#### Code:
```C
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
```

### Query
This functions asks the user for last name of the contacts he is searching for and prints all matching results. It uses a function called [`printOneContact()`](#printOneContact) to print the contact or contacts found
> Note: You can click on the function name to reference its details.
#### Code:
```C
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
```
#### Sample Run:
![Query sample run](img/query1.png "Query sample run")
![Query sample run](img/query2.png "Query sample run")

### Add
This Function adds a contact to the phone book it asks the user for last name, first name, date of birth formatted as (dd-mm-yyyy), address, phone number, and email address. When the contact is added successfully it asks the user it he wants to add another one. 

It validates the user input. It keeps asking the user if he enters invalid input. It uses for that three helping functions  [`validDate()`](#valid-date), [`validEmail()`](#valid-email), and [`validPhone()`](#valid-phone). 

> Note: You can click on any of the helping functions for more information.
#### Code:
```C
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
```
#### Sample Runs:

**Handing various errors**

![add sample run](img/add.png)

### Delete
This function asks the user for the last and first name of the contact he wants to delete and delete all matching contacts. It achieves that by copying all the contacts that won't be deleted into a new array of contacts and updates the main global array of contacts and the global count for contacts
 In addition, It prints all deleted contacts so the user can get good indication that the contact is deleted. It gets help from [`printContacts()`](#printContact) function with prints all the contacts in the array. Also it gives error it the contact is not found.
> Note: You can click on the function name to reference it.
#### Code:
```C
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
```
#### Sample Runs:

![Delete](img/delete1.png)

In case of the contact not found:

![Delete](img/delete2.png)

### Modify
This function asks the user for the last name he wants to modify and searches for it. if it found one contact it lets the user modify it directly and prints the contact information but if it founds more than one contact it shows a menu where the user chooses which contact he want to modify

### Print
It prints a menu where the user can choose from printing contacts normally, sorted by last name, or sorted by date of birth. It validates user input
#### Code:

```C
void printMenu()
{
    char input[10];
    char menuItems[3][MAXSTRING] = {"Normal", "Sort by last name.", "Sort by date of birth."};
    int menuSize = sizeof(menuItems) / sizeof(menuItems[0]);

    printf("\nChoose the number of your option:\n");
    for (i = 0; i < menuSize; i++)
        printf("(%d)  %s\n", (i + 1), menuItems[i]);
    scanf("%s", input);

    switch (atoi(input))
    {
    case 1:
        printContacts(contacts);
        break;
    case 2:
        sortByLastName();
        break;
    case 3:
        sortByDate();
        break;

    default:
        printf("\nError! Unexpected input. \n");
        pause();
        printMenu();
        break;
    }
}
```
#### Sample Run:
**Normal**

![print sample run](img/print1.png)

**Sorted by Last Name**

![print sample run](img/print2.png)

**Sorted by Date of Birth**

![print sample run](img/print3.png)

**Error Handling**

![print sample run](img/printError.png)


Save
This function saves all the information of all the contacts in a file. It simply writes all what is inside the global array of Contacts into the same file used in Load() function.
Quit 
This function simply allows the user to quit from the program if he/she wants. It first displays a warning message if any modification is done on the global array of Contacts and that modification isn’t saved. If that modification is saved before entering the Quit() function, then no warning message will be displayed. If no modification occurred at all, then again no warning message will be displayed. Then the user is asked “Are you sure you want to quit(y/n)?”. The function keeps asking the user to enter a valid input if the input isn’t “y” or “n”. If “y”, the program ends. If “n”, the program will return to Menu() function.
Sort by last name
This function sorts the global array of Contacts by last name with the help of the built-in function qsort(). qsort() itself needs a helping function. So, compareNames() function is that helping function.  The role of compareNames() function is to compare two items and return an integer value less than zero if the first item is less than second item , return zero if both items are equal, or return an integer value more than zero if the first item is greater than second item.
