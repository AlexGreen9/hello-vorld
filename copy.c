#include <stdio.h>
#include "copy.h"
#include <string.h>
#include "two.h"
#include "one.h"
#include "person.h"
#define MAX_CONTACTS 100
#define MAX_NAME_LENGTH 50
#define MAX_JOB_LENGTH 50
#define MAX_PHONE_LENGTH 20
#define MAX_EMAIL_LENGTH 50
#define MAX_SOCIAL_LENGTH 50
#define MAX_CONTACTS 100
int size = 0;



struct Contact contacts[MAX_CONTACTS];
int num_contacts = 0;
void add_contact() {
    if (num_contacts < MAX_CONTACTS) {
        struct Contact new_contact;
        printf("Enter first name: ");
        scanf("%s", new_contact.first_name );
        printf("Enter last name: ");
         scanf("%s", new_contact.last_name);
        printf("Enter job: ");
        fgets(contacts[num_contacts].wor.job, MAX_JOB_LENGTH , stdin);
        printf("Enter phone number: ");
        fgets(contacts[num_contacts].phone_numbers, MAX_PHONE_LENGTH, stdin);
        printf("Enter email address: ");
        fgets(contacts[num_contacts].soci.email, MAX_EMAIL_LENGTH, stdin);
        printf("Enter social media profile: ");
        fgets(contacts[num_contacts].soci.social_media, MAX_SOCIAL_LENGTH, stdin);
        char empty_string[] = " ";
        strcpy(new_contact.empty_string, empty_string);
    } else {
        printf("Cannot add more contacts. Contact list is full.\n");
    }
}
void edit_contact() {
    char search_name[MAX_NAME_LENGTH];
    printf("Enter first name of contact to edit: ");
    scanf("%s", search_name);
    int contact_index = -1;
    for (int i = 0; i < num_contacts; i++) {
        if (strcmp(contacts[i].first_name, search_name) == 0) {
            contact_index = i;
            break;
        }
    }
    if (contact_index != -1) {
        printf("Enter new job: ");
        scanf("%s", contacts[contact_index].wor.job);
        printf("Enter new phone number: ");
        scanf("%s", contacts[contact_index].phone_numbers);
        printf("Enter new email address: ");
        scanf("%s", contacts[contact_index].soci.email);
        printf("Enter new social media profile: ");
        scanf("%s", contacts[contact_index].soci.social_media);
        printf("Contact edited successfully.\n");
    } else {
        printf("Contact not found.\n");
    }
}
void delete_contact() {
    char search_name[MAX_NAME_LENGTH];
    printf("Enter first name of contact to delete: ");
    scanf("%s", search_name);
    int contact_index = -1;
    for (int i = 0; i < num_contacts; i++) {
        if (strcmp(contacts[i].first_name, search_name) == 0) {
            contact_index = i;
            break;
        }
    }
    if (contact_index != -1) {
        for (int i = contact_index; i < num_contacts - 1; i++) {
            contacts[i] = contacts[i + 1];
        }
        num_contacts--;
        printf("Contact deleted successfully.\n");
    } else {
        printf("Contact not found.\n");
    }
}
void print_contact(struct Contact contact) {
    printf("Name: %s %s\n", contact.first_name, contact.last_name);
    printf("Job: %s\n", contact.wor.job);
    printf("Phone: %s\n", contact.phone_numbers);
    printf("Email: %s\n", contact.soci.email);
    printf("Social Media: %s\n", contact.soci.social_media);
    printf("\n");
}
void list_contacts() {
    if (num_contacts == 0) {
        printf("No contacts found.\n");
    } else {
        for (int i = 0; i < num_contacts; i++) {
            print_contact(contacts[i]);
        }
    }
}
