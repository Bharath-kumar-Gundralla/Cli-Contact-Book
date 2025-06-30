#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook, int sortCriteria)
{
    int i, j;
    Contact temp;
    switch (sortCriteria)
    {
    case 1: // list by name

        for (i = 0; i < addressBook->contactCount - 1; i++)//i starts from 0 so loop should run upto 99 count 
        {
            for (j = 0; j < addressBook->contactCount - i - 1; j++)
            {
                if (strcmp(addressBook->contacts[j].name,addressBook->contacts[j + 1].name) > 0)
                {
                    temp = addressBook->contacts[j];//sorting the contacts
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                    addressBook->contacts[j + 1] = temp;
                }
            }
            
        }
        break;

    case 2: // list by phone number
        for (i = 0; i < addressBook->contactCount-1; i++)
        {
            for (j = 0; j < addressBook->contactCount-i-1; j++)
            {
                if (strcmp(addressBook->contacts[j].phone,addressBook->contacts[j + 1].phone) > 0)
                {
                    temp = addressBook->contacts[j];//sorting method 
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                    addressBook->contacts[j + 1] = temp;
                }
            }
        }
        break;
    case 3: // list by email

        for (i = 0; i < addressBook->contactCount - 1; i++)
        {
            for (j = 0; j < addressBook->contactCount - i - 1; j++)
            {
                if (strcmp(addressBook->contacts[j].email, addressBook->contacts[j + 1].email) > 0)
                {
                    temp = addressBook->contacts[j];//sorting method
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                    addressBook->contacts[j + 1] = temp;
                }
            }
        }
        break;
    default:
        printf("Invalid option\n");//option should be selected should be between 1 to 3
        return;
    }
   printf("\n contact list : \n");//printing the contacts list
   printf(".....................................................................................................\n");
   printf("NAME\t\t\t\tPHONE NUMBER\t\t\tEMAIL\n");
    printf("......................................................................................................\n");
   for (i = 0; i < addressBook->contactCount; i++) // printing contact details in order
   {
       printf("%s\t\t\t%s\t\t\t%s\n", addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
   }
}

void initialize(AddressBook *addressBook)

{
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    loadContactsFromFile(addressBook);
}
void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program
}

void createContact(AddressBook *addressBook)
{
    char name[100], phone[100], email[100];
    do
    {
        printf("Enter name : "); // asking user to enter name.
        scanf(" %[^\n]", name);
    } while (isvalidname(name)); // function call to validate the name ie name should be alphabets only.
   
    while (1)
    {
        printf("Enter phone number: ");
        scanf(" %s", phone);

        if (isvalidnum(phone)) // to check number is valid or not
            continue;

        if (isuniqphone(addressBook, phone)) // to check number is unique or not 
        {
            printf("ERROR: Phone number already exists.\n");
            continue;
        }

        break; // if valid and unique
    }
   
    while (1)
    {
        printf("Enter email: ");
        scanf(" %s", email);

        if (isvalidemail(email)) // to check the email is valid or not
            continue;

        if (isuniqemail(addressBook, email)) // to check the email is unique or not 
        {
            printf("ERROR: Email already exists.\n");
            continue;
        }

        break; // if valid and unique
    }

    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email, email);
    addressBook->contactCount++;
    printf("Contact added successfully!\n"); // if all conditions are satisfied contact will be saved .
}

int isvalidname(char *name) // function defination to validate the name.
{
    for (int i = 0; i < strlen(name); i++)
    {
        if (!isalpha(name[i]) && name[i] != ' ')
        {
            printf("ERROR : Enter alphabets and spaces only.\n");

            return 1; // invalid name return 1
        }
    }
    return 0; // valid name return 0
}

int isvalidnum(char *phone) // function defination to check valid phone number
{
    int length = strlen(phone);
    if (length != 10) // phone number must be 10 numbers only.
    {
        printf("\nERROR : Phone number must be exactly 10 digits.\n");
        return 1;
    }
    for (int i = 0; i < length; i++)
    {
        if (!isdigit(phone[i]))
        {
            printf("ERROR : Enter digits only.\n");
            return 1; // return 1 invalid phonenumber
        }
    }

    return 0; // if valid number return 0
}

int isvalidemail(char *email)
{
    int atcount = 0, dotcount = 0;
    for (int i = 0; i < strlen(email); i++)
    {
        if ((email[i] >= 'A' && email[i] <= 'Z') || (email[i] >= 'a' && email[i] <= 'z') ||
            (email[i] >= '0' && email[i] <= '9') || email[i] == '@' || email[i] == '.' || email[i] == '_')
        {
            if (email[i] == '@')
            {
                atcount++; // if @ found then increment atcount.
            }
            if (email[i] == '.')
            {
                dotcount++; // if dot(.) found increment dotcount.
            }
        }
        else
        {
            printf("ERROR : Invalid characters in email.\n");
            return 1;
        }
    }
    if (atcount != 1 || dotcount != 1) // email must need to contain atleast one @ and one . in it.
    {
        printf("ERROR : Email must contain 1 '@' and  1 '.'\n");
        return 1;
    }
    return 0;
}
int isuniqphone(AddressBook *addressBook, char *phone) // function defination to to validate the number is unique or not.
{
    for (int i = 0; i < addressBook->contactCount; i++)
        if (strcmp(addressBook->contacts[i].phone, phone) == 0) // compare the newly entered number with existing numbers in addressbook.
        {

            return 1; // if found return 1
            break;
        }
    return 0; // if not found means it is unique number
}
int isuniqemail(AddressBook *addressBook, char *email) // function defination to check email is unique or not.
{
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, email) == 0) // compare newly entered phone number with remaining emails in addressbook
        {
            return 1; // if found return 1
            break;
        }
    }
    return 0; // if not found return 0
}
void searchContact(AddressBook *addressBook) // searching the contact in addressbook
{
    int option, found = 0;
    char searchInput[100];

    printf("\nselect option to search \n"); // options to search by name,phone number,email.
    printf("1. Name\n");
    printf("2. Phone Number\n");
    printf("3. Email\n");
    printf("Enter your option: ");
    scanf("%d", &option);

    switch (option)
    {
    case 1: // option 1 search by name
        int index1=1;
        printf("Enter name to search: "); // asking user to enter the name
        scanf(" %[^\n]", searchInput);
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strstr(addressBook->contacts[i].name, searchInput)) // checking the name in addressbook.
            {
                if (found == 0)
                {
                    printf("........................................................................................................\n");
                    printf("s.no\tname\t\t\tphone number\t\t\temail\n");
                    printf(".........................................................................................................\n");
                }
                printf("%d\t%s\t\t\t%s\t\t\t%s\n", index1++, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                found = 1;
            }
        }
        if (!found)
            printf("\nContact not found.\n"); // if not found displaying conatct not found
            break;
    case 2:  // search  by phonenumber.
       int index2=1;
        printf("Enter phone number to search: "); // enter the number to search
        scanf("%s", searchInput);
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strstr(addressBook->contacts[i].phone, searchInput)) // comparing the name with the phone numbers in addressbook
            {
                if (found == 0)
                {
                    printf("........................................................................................................\n");
                    printf("s.no\tname\t\t\tphone number\t\t\t\temail\n");
                    printf(".........................................................................................................\n");
                }
                printf("%d\t%s\t\t\t%s\t\t\t\t%s\n", index2++, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                found = 1;
            }
        }
        if (!found)
            printf("\nContact not found.\n"); // if not found displaying conatct not found
        break;
    case 3: // search by email
    int index3=1;
        printf("Enter email to search: "); // enter email to search
        scanf("%s", searchInput);
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strstr(addressBook->contacts[i].email, searchInput))
            {
                if (found == 0)
                {
                    printf("........................................................................................................\n");
                    printf("s.no\tname\t\t\tphone number\t\t\temail\n");
                    printf(".........................................................................................................\n");
                }
                printf("%d\t%s\t\t\t%s\t\t\t%s\n", index3++, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                found = 1;
            }
        }
        if (!found)
        {
            printf("\nContact not found.\n"); // if not found displaying conatct not found
        }
        break;
    default:
        printf("Invalid option! Please enter 1, 2 or 3.\n");
    }
}
void editContact(AddressBook *addressBook) // edit contact
{
    char searchinput[50];
    int choice, found = 0, index = 1, editIndex;
    int matchedindices[MAX_CONTACTS];

    printf("\nChoose how you want to search:\n");
    printf("1. Search by Name\n");
    printf("2. Search by Phone Number\n");
    printf("3. Search by Email\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1: // Search by Name
        printf("Enter the name to search: ");
        scanf(" %[^\n]", searchinput);

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strstr(addressBook->contacts[i].name, searchinput))
            {
                if (found == 0)
                {
                    printf("........................................................................................................\n");
                    printf("S.No\tName\t\t\t\tPhone Number\t\t\tEmail\n");
                    printf("........................................................................................................\n");
                }
                printf("%d\t%s\t\t\t\t%s\t\t\t%s\n", index, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                matchedindices[index-1] = i;
                index++;
                found = 1;
            }
        }
        break;

    case 2: // Search by Phone Number
        printf("Enter the phone number to search: ");
        scanf("%s", searchinput);

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strstr(addressBook->contacts[i].phone, searchinput))
            {
                if (found == 0)
                {
                    printf("........................................................................................................\n");
                    printf("S.No\tName\t\t\t\tPhone Number\t\t\tEmail\n");
                    printf("........................................................................................................\n");
                }
                printf("%d\t%s\t\t\t\t%s\t\t\t%s\n", index, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                matchedindices[index-1] = i;
                index++;
                found = 1;
            }
        }
        break;

    case 3: // Search by Email
        printf("Enter the email to search: ");
        scanf("%s", searchinput);

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strstr(addressBook->contacts[i].email, searchinput))
            {
                if (found == 0)
                {
                    printf("........................................................................................................\n");
                    printf("S.No\tName\t\t\t\tPhone Number\t\t\tEmail\n");
                    printf("........................................................................................................\n");
                }
                printf("%d\t%s\t\t\t\t%s\t\t\t%s\n", index, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                matchedindices[index-1] = i;
                index++;
                found = 1;
            }
        }
        break;

    default:
        printf("Invalid option.\n");
        return;
    }

    if (!found)
    {
        printf("No contacts found!\n");
        return;
    }

    int selectedsno;
    printf("\nSelect the S.No of the contact you want to edit: ");
    scanf("%d", &selectedsno);

    if (selectedsno < 1 || selectedsno >= index)
    {
        printf("Invalid index selected!\n");
        return;
    }

    editIndex = matchedindices[selectedsno - 1];

    printf("\nSelect what you want to edit:\n");
    printf("1. Name\n");
    printf("2. Phone Number\n");
    printf("3. Email\n");
    printf("Enter your option: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1: // Edit Name
    {
        char newname[50];
        printf("Enter new name: ");
        scanf(" %[^\n]", newname);

        if (isvalidname(newname) == 0)
        {
            strcpy(addressBook->contacts[editIndex].name, newname);
            printf("Name updated successfully!\n");
        }
        else
        {
            printf("Invalid name! Only alphabets allowed.\n");
        }
        break;
    }
    case 2: // Edit Phone Number
    {
        char newphone[15];
        printf("Enter new phone number: ");
        scanf("%s", newphone);

        if (isvalidnum(newphone) == 0)
        {
            strcpy(addressBook->contacts[editIndex].phone, newphone);
            printf("Phone number updated successfully!\n");
        }
        else
        {
            printf("Invalid phone number!\n");
        }
        break;
    }
    case 3: // Edit Email
    {
        char newemail[50];
        printf("Enter new email: ");
        scanf("%s", newemail);

        if (isvalidemail(newemail) == 0)
        {
            strcpy(addressBook->contacts[editIndex].email, newemail);
            printf("Email updated successfully!\n");
        }
        else
        {
            printf("Invalid email format!\n");
        }
        break;
    }
    default:
        printf("Invalid option selected!\n");
        break;
    }
}

void deleteContact(AddressBook *addressBook)
{
    char searchinput[50];
    int choice, found = 0, index = 1, deleteIndex;
    char conform;
    int matchedindices[MAX_CONTACTS];

    printf("\nChoose how you want to search for deletion:\n");//displaying options to user to select option to search contact
    printf("1. Search by Name\n");
    printf("2. Search by Phone Number\n");
    printf("3. Search by Email\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1: // Search by Name
        printf("Enter the name to search: ");
        scanf(" %[^\n]", searchinput);// taking search input as input to search by name

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strstr(addressBook->contacts[i].name, searchinput))
            {
                if (found==0)
                {
                    printf("........................................................................................................\n");
                    printf("S.No\tName\t\t\t\tPhone Number\t\t\tEmail\n");
                    printf("........................................................................................................\n");
                }
                printf("%d\t%s\t\t\t\t%s\t\t\t%s\n", index, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                matchedindices[index - 1] = i;//to track the orginal index value in addressbook
                index++;
                found = 1;//if the name is found in addressbook found =1
            }
        }
        break;

    case 2: // Search by Phone number 
        printf("Enter the phone number to search: ");
        scanf(" %[^\n]", searchinput);//asking user to enter the phone number to search 

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strstr(addressBook->contacts[i].phone, searchinput))//searching the user entered phno with all the phno in addressbook
            {
                if (found==0)
                {
                    printf("........................................................................................................\n");
                    printf("S.No\tName\t\t\t\tPhone Number\t\t\tEmail\n");
                    printf("........................................................................................................\n");
                }
                printf("%d\t%s\t\t\t\t%s\t\t\t%s\n", index, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                matchedindices[index - 1] = i;
                index++;
                found = 1;//if the phone number found in addressbook then found becomes 1
            }
        }
        break;

    case 3: // Search by Email 
        printf("Enter the email to search: ");
        scanf(" %[^\n]", searchinput);//asking user to enter the email to search 

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strstr(addressBook->contacts[i].email, searchinput))//comparing the user entered email with all the emails in addressbook
            {
                if (found==0)
                {
                    printf("........................................................................................................\n");
                    printf("S.No\tName\t\t\t\tPhone Number\t\t\tEmail\n");
                    printf("........................................................................................................\n");
                }
                printf("%d\t%s\t\t\t\t%s\t\t\t%s\n", index, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                matchedindices[index - 1] = i;
                index++;
                found = 1;// if email found in the adressbook found becomews 1 
            }
        }
        break;

    default:
        printf("Invalid choice!\n");//error message to say entred choice is invalid ie it should be 1-3
        return;
    }

    if (!found)
    {
        printf("No matching contacts found.\n");//if not found error message to say contact not found 
        return;
    }

    printf("Enter the serial number of the contact to delete: ");
    scanf("%d", &deleteIndex);//asking user to enter the serial no of the contact that user want to delete

    if (deleteIndex < 1 || deleteIndex >= index)
    {
        printf("Invalid serial number.\n");//error message if the s.no is less than 1 (or) greater than the limit
        return;
    }

    printf("Are you sure you want to delete this contact? (y/n): ");
    while ((getchar()) != '\n'); 
    scanf("%c", &conform);//asking user whether to delete the contact or not for conformation.

    if (conform == 'y'||conform=='Y')//if user selects y ie yes the conatact is deleted 
    {
        int actualIndex = matchedindices[deleteIndex - 1];
        for (int j = actualIndex; j < addressBook->contactCount - 1; j++)
        {
            addressBook->contacts[j] = addressBook->contacts[j + 1];
        }
        addressBook->contactCount--;
        printf("Contact deleted successfully.\n");//prompt to say contact is deleted successfully
    }
    else if (conform == 'n'||conform=='N')
    {
        printf("Deletion cancelled.\n");//prompt to say the deletion is cancelled if user select NO
    }
    else
    {
        printf("Invalid option. Deletion aborted.\n");//error message do display if the user selects any another than y or n
    }
}
