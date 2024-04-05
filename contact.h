#ifndef CONTACT_H
#define CONTACT_H

typedef struct Contact {
    char lastname[50];
    char firstname[50];
    char job[50];
    char phone[15];
    char email[50];
    char social_media[50];
    struct Contact* next;
    struct Contact* prev;
} Contact;

Contact* create_contact(char* lastname, char* firstname, char* job, char* phone, char* email, char* social_media);

void insert_contact(Contact** list, Contact* new_contact);

void print_contacts(Contact* list);

void delete_contact(Contact** list, char* lastname, char* firstname);

#endif
