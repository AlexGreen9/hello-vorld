#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact {
    char firstName[50];
    char lastName[50];
    char phoneNumber[20];
    char email[50];
    char workplace[50];
    struct Contact* prev;
    struct Contact* next;
};

struct Contact *head = NULL;
struct Contact *tail = NULL;

void addContact();
void displayContacts();
void saveContactsToFile();
void loadContactsFromFile();

int main() {
    loadContactsFromFile();

    while(1) {
        printf("\n1. Add contact\n2. Display contacts\n3. Exit\n");
        int choice;
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addContact();
                break;
            case 2:
                displayContacts();
                break;
            case 3:
                saveContactsToFile();
                exit(0);
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}

void addContact() {
    struct Contact *newContact = malloc(sizeof(struct Contact));
    
    printf("Enter first name: ");
    scanf("%s", newContact->firstName);
    printf("Enter last name: ");
    scanf("%s", newContact->lastName);
    printf("Enter phone number: ");
    scanf("%s", newContact->phoneNumber);
    printf("Enter email: ");
    scanf("%s", newContact->email);
    printf("Enter workplace: ");
    scanf("%s", newContact->workplace);
    
    newContact->prev = tail;
    newContact->next = NULL;

    if (head == NULL) {
        head = newContact;
        tail = newContact;
    } else {
        tail->next = newContact;
        tail = newContact;
    }
}

void displayContacts() {
    struct Contact *current = head;
    while(current != NULL) {
        printf("\nName: %s %s\nPhone: %s\nEmail: %s\nWorkplace: %s\n", current->firstName, current->lastName, current->phoneNumber, current->email, current->workplace);
        current = current->next;
    }
}

void saveContactsToFile() {
    FILE *file = fopen("contacts.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct Contact *current = head;
    while(current != NULL) {
        fprintf(file, "%s %s %s %s %s\n", current->firstName, current->lastName, current->phoneNumber, current->email, current->workplace);
        current = current->next;
    }

    fclose(file);
}

void loadContactsFromFile() {
    FILE *file = fopen("contacts.txt", "r");
    if (file == NULL) {
        printf("No saved contacts found.\n");
        return;
    }

    while(!feof(file)) {
        struct Contact *newContact = malloc(sizeof(struct Contact));
        fscanf(file, "%s %s %s %s %s\n", newContact->firstName, newContact->lastName, newContact->phoneNumber, newContact->email, newContact->workplace);
        newContact->prev = tail;
        newContact->next = NULL;

        if (head == NULL) {
            head = newContact;
            tail = newContact;
        } else {
            tail->next = newContact;
            tail = newContact;
        }
    }

    fclose(file);
}
