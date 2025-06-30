#include <stdio.h>
#include "file.h"
void saveContactsToFile(AddressBook *addressBook) 
{
  FILE *fptr=fopen("contacts.csv","w");//creating contact.csv file and opening the file in write mode
  if(fptr==NULL)
  {
    printf("cannot open the file\n");//if it is null it prints an error.
    return;
  }
  for(int i=0;i<addressBook->contactCount;i++)//loop to save one after another 
  {
      fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
      //saving name,ph number,email to .csv file 
  }
  fclose(fptr);//close the file
}

void loadContactsFromFile(AddressBook *addressBook)
{
    int i=0;
    FILE *fptr=fopen("contacts.csv","r");//opening an contact.csv file in read mode.
    if(fptr==NULL)
    {
        printf("file not found \n");//print error message and return 
        return;
    }
    while(fscanf(fptr,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email) > 0)
    //getting contacts ie name,phone number,emails and updating them in addressbook contacts
    {
        i++;//incrementing contactcount 
    }
    addressBook->contactCount=i;// updating the i value in addressbook contactcount
    fclose(fptr);//close the file 
    
}
