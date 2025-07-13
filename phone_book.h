#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include<stdio.h>
#include<stdlib.h>
#include<stdio_ext.h>
#include<string.h>
#include<ctype.h>

#define MAX_NAME_LENGTH 50
#define MAX_PHONE_LENGTH 15
#define MAX_EMAIL_LENGTH 50
#define MAX_ADDRESS_LENGTH 100
#define FILENAME "phonebook.dat"

typedef struct PhoneNumber
{
    char number[MAX_PHONE_LENGTH];
    struct PhoneNumber *next;
}PhoneNumber;

typedef struct Contact
{
    char name[MAX_NAME_LENGTH];
    PhoneNumber *phoneHead;
    char email[MAX_EMAIL_LENGTH];
    char address[MAX_ADDRESS_LENGTH];
    struct Contact *next;
}Contact;

// Function prototypes
void displayMenu();
void toLowerCase(char *str);
Contact* createContact();
void printContacts(Contact *head);
Contact* deleteContact(Contact *head, const char *name);
Contact* findContact(Contact *head, const char *name);
void editContact(Contact *head, const char *name);
void saveContactsToFile(Contact *head);
Contact* loadContactsFromFile();
void freeContacts(Contact *head);
void addPhoneNumber(Contact *contact);
int isDuplicateContact(Contact *head, const char *name);

#endif
