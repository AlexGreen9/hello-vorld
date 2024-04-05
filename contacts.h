#ifndef CONTACTS_H
#define CONTACTS_H

typedef struct Contact {
    char firstName[50];
    char lastName[50];
    char jobTitle[50];
    char workplace[50];
    char phone[15];
    char email[50];
    char socialMedia[50];
    struct Contact* next;
    struct Contact* prev;
} Contact;

void insertContact(Contact** head, Contact* newContact);
int deleteContact(Contact** head, char* firstName, char* lastName);
void displayContacts(Contact* head);
Contact* createContact(char firstName[], char lastName[], char jobTitle[], char workplace[], char phone[], char email[], char socialMedia[]);

#endif
