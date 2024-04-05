#include <stdio.h>
#include <stdlib.h>
#include "contact.h"

int main() {
    Contact* contacts_list = NULL;
    char choice;
    char lastname[50];
    char firstname[50];
    char job[50];
    char phone[15];
    char email[50];
    char social_media[50];

    do {
        printf("\nMenu:\n");
        printf("1. Add a contact\n");
        printf("2. View all contacts\n");
        printf("3. Delete a contact\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch(choice) {
            case '1':
                printf("Enter lastname: ");
                scanf("%s", lastname);
                printf("Enter firstname: ");
                scanf("%s", firstname);
                printf("Enter job: ");
                scanf("%s", job);
                printf("Enter phone: ");
                scanf("%s", phone);
                printf("Enter email: ");
                scanf("%s", email);
                printf("Enter social media: ");
                scanf("%s", social_media);
                
                Contact* new_contact = create_contact(lastname, firstname, job, phone, email, social_media);
                insert_contact(&contacts_list, new_contact);
                printf("Contact added successfully.\n");
                break;
            case '2':
                printf("Contacts:\n");
                print_contacts(contacts_list);
                break;
            case '3':
                printf("Enter the lastname of the contact you want to delete: ");
                scanf("%s", lastname);
                printf("Enter the firstname of the contact you want to delete: ");
                scanf("%s", firstname);

                delete_contact(&contacts_list, lastname, firstname);
                printf("Contact deleted successfully.\n");
                break;
            case '4':
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != '4');

    return 0;
}


