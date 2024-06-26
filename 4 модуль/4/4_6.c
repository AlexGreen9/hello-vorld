
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>

#define MAX_LENGTH 50

typedef struct Contact {
    char firstName[MAX_LENGTH];
    char lastName[MAX_LENGTH];
    char phoneNumber[MAX_LENGTH];
    char email[MAX_LENGTH];
    char workplace[MAX_LENGTH];
    struct Contact* next;
    struct Contact* prev;
} Contact;

Contact* head = NULL;
sem_t *sem;

void read_contacts_from_file() {
    FILE *file = fopen("contacts.txt", "r");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    char line[MAX_LENGTH];
    while(fgets(line, sizeof(line), file)) {
        Contact* newContact = malloc(sizeof(Contact));
        sscanf(line, "%s %s %s %s %s", newContact->firstName, newContact->lastName, newContact->phoneNumber, newContact->email, newContact->workplace);
        newContact->next = head;
        if (head != NULL) {
            head->prev = newContact;
        }
        head = newContact;
    }

    fclose(file);
}

void write_contacts_to_file() {
    FILE *file = fopen("contacts.txt", "w");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    Contact* current = head;
    while (current != NULL) {
        fprintf(file, "%s %s %s %s %s\n", current->firstName, current->lastName, current->phoneNumber, current->email, current->workplace);
        current = current->next;
    }

    fclose(file);
}

int main() {
    sem = sem_open("/my_sem", O_CREAT, 0644, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    read_contacts_from_file();

    // Блокировка доступа к файлу
    sem_wait(sem);

    // Модификация файла
    // Пример добавления нового контакта
    Contact* newContact = malloc(sizeof(Contact));
    strcpy(newContact->firstName, "Jane");
    strcpy(newContact->lastName, "Smith");
    strcpy(newContact->phoneNumber, "9876543210");
    strcpy(newContact->email, "jane.smith@example.com");
    strcpy(newContact->workplace, "Company");
    newContact->next = head;
    if (head != NULL) {
        head->prev = newContact;
    }
    head = newContact;

    // Разблокировка доступа к файлу
    sem_post(sem);

    // Вывод всех контактов
    Contact* current = head;
    while (current != NULL) {
        printf("%s %s %s %s %s\n", current->firstName, current->lastName, current->phoneNumber, current->email, current->workplace);
        current = current->next;
    }

    write_contacts_to_file();

    sem_close(sem);
    sem_unlink("/my_sem");

    return 0;
}
