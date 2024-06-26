
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_LENGTH 50
#define FILENAME "contacts.txt"

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

void read_contacts_from_file() {
    FILE *file = fopen(FILENAME, "r");
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
    FILE *file = fopen(FILENAME, "w");
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

void sigusr1_handler(int signum) {
    // Блокировка доступа к файлу
    printf("Received SIGUSR1, waiting for SIGUSR2...\n");
}

void sigusr2_handler(int signum) {
    // Разблокировка доступа к файлу
}

int main() {
    int fd;
    pid_t pid;
    struct stat statbuf;
    void* addr;

    signal(SIGUSR1, sigusr1_handler);
    signal(SIGUSR2, sigusr2_handler);

    fd = open(FILENAME, O_RDWR | O_CREAT, 0666);
    ftruncate(fd, sizeof(Contact)*10); // Выделяем память под 10 контактов

    addr = mmap(NULL, sizeof(Contact)*10, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED) {
        perror("Error mapping file");
        exit(1);
    }

    read_contacts_from_file();

    printf("Contacts:\n");
    Contact* current = head;
    while (current != NULL) {
        printf("%s %s %s %s %s\n", current->firstName, current->lastName, current->phoneNumber, current->email, current->workplace);
        current = current->next;
    }

    pid = fork();

    if (pid == 0) {
        // Дочерний процесс
        sleep(2); // Имитация чтения файла
        printf("Child process reading file...\n");
        kill(getppid(), SIGUSR1); // Отправляем сигнал родительскому процессу о готовности
        pause(); // Ждем пока родительский процесс завершит запись
    } else {
        // Родительский процесс
        sigset_t mask;
        sigemptyset(&mask);
        sigaddset(&mask, SIGUSR1);
        sigprocmask(SIG_BLOCK, &mask, NULL); // Блокируем SIGUSR1

        printf("Parent process modifying file...\n");
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
        kill(pid, SIGUSR2);

        sigsuspend(&mask); // Ждем SIGUSR1 от дочернего процесса
        printf("Parent process received data from child\n");

        write_contacts_to_file();
    }

    munmap(addr, sizeof(Contact)*10);
    close(fd);
    return 0;
}
