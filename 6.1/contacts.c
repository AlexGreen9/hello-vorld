#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contacts.h"

void insertContact(Contact** head, Contact* newContact) {
    if (*head == NULL || strcmp(newContact->lastName, (*head)->lastName) < 0) {
        newContact->next = *head;
        if (*head != NULL) {
            (*head)->prev = newContact;
        }
        *head = newContact;
    } else {
        Contact* current = *head;
        while (current->next != NULL && strcmp(newContact->lastName, current->next->lastName) > 0) {
            current = current->next;
        }
        newContact->next = current->next;
        if (current->next != NULL) {
            current->next->prev = newContact;
        }
        current->next = newContact;
        newContact->prev = current;
    }
}

void deleteContact(Contact** head, char* firstName, char* lastName) {
    Contact* current = *head;
    while (current != NULL) {
        if (strcmp(current->firstName, firstName) == 0 && strcmp(current->lastName, lastName) == 0) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                *head = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            }
            free(current);
            return;
        }
        current = current->next;
    }
    printf("Contact not found\n");
}

void displayContacts(Contact* head) {
    Contact* current = head;
    while (current != NULL) {
        printf("Name: %s %s\n", current->firstName, current->lastName);
        printf("Job Title: %s\nWorkplace: %s\n", current->jobTitle, current->workplace);
        printf("Phone: %s\nEmail: %s\nSocial Media: %s\n", current->phone, current->email, current->socialMedia);
        printf("\n");
        current = current->next;
    }
}

Contact* createContact(char firstName[], char lastName[], char jobTitle[], char workplace[], char phone[], char email[], char socialMedia[]) {
    Contact* newContact = (Contact*)malloc(sizeof(Contact));
    if (newContact == NULL) {
        printf("Memory allocation failed");
        return NULL;
    }
    strcpy(newContact->firstName, firstName);
    strcpy(newContact->lastName, lastName);
    strcpy(newContact->jobTitle, jobTitle);
    strcpy(newContact->workplace, workplace);
    strcpy(newContact->phone, phone);
    strcpy(newContact->email, email);
    strcpy(newContact->socialMedia, socialMedia);
    newContact->next = NULL;
    newContact->prev = NULL;
    return newContact;
}
