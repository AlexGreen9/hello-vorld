#include <stdio.h>
#include <string.h>
#include "contacts.h"

void printMenu() {
    printf("\n===== Contact Manager =====\n");
    printf("1. Add Contact\n");
    printf("2. Delete Contact\n");
    printf("3. Display All Contacts\n");
    printf("4. Exit\n");
    printf("===========================\n");
    printf("Enter your choice: ");
}

int main() {
    Contact* head = NULL;
    int choice;
    char firstName[50], lastName[50];

    do {
        printMenu();
        scanf("%d", &choice);
        getchar(); // Capture newline character

        switch(choice) {
            case 1: // Add Contact
                {
                    char jobTitle[50], company[50], phoneNumber[15], email[50], twitter[50];
                    printf("Enter first_name: ");
                    fgets(firstName, 50, stdin);
                    firstName[strcspn(firstName, "\n")] = 0;  // Remove newline character
                    printf("Enter last_name: ");
                    fgets(lastName, 50, stdin);
                    lastName[strcspn(lastName, "\n")] = 0;  // Remove newline character
                    printf("Enter job: ");
                    fgets(jobTitle, 50, stdin);
                    jobTitle[strcspn(jobTitle, "\n")] = 0;  // Remove newline character
                    printf("Enter company: ");
                    fgets(company, 50, stdin);
                    company[strcspn(company, "\n")] = 0;  // Remove newline character
                    printf("Enter phone: ");
                    fgets(phoneNumber, 15, stdin);
                    phoneNumber[strcspn(phoneNumber, "\n")] = 0;  // Remove newline character
                    printf("Enter email: ");
                    fgets(email, 50, stdin);
                    email[strcspn(email, "\n")] = 0;  // Remove newline character
                    printf("Enter social media: ");
                    fgets(twitter, 50, stdin);
                    twitter[strcspn(twitter, "\n")] = 0;  // Remove newline character

                    Contact* newContact = createContact(firstName, lastName, jobTitle, company, phoneNumber, email, twitter);
                    insertContact(&head, newContact);
                    printf("Contact added successfully.\n");
                }
                break;
            case 2: // Delete Contact
                printf("Enter first name of contact to delete: ");
                fgets(firstName, 50, stdin);
                firstName[strcspn(firstName, "\n")] = 0;  // Remove newline character
                printf("Enter last name of contact to delete: ");
                fgets(lastName, 50, stdin);
                lastName[strcspn(lastName, "\n")] = 0;  // Remove newline character

                if(deleteContact(&head, firstName, lastName))
                    printf("Contact deleted successfully.\n");
                else
                    printf("Contact not found.\n");
                
                break;
            case 3: // Display All Contacts
                displayContacts(head);
                break;
            case 4: // Exit
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while(choice != 4);

    return 0;
}

