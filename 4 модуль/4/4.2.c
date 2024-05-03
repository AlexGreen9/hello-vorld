#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <string.h>  // Добавляем заголовочный файл для функции strlen

#define SEM_KEY 1000

int main() {
    int pid;
    int file_descriptor;
    char init_str[10] = "0";  // Начальное число для записи в файл

    file_descriptor = open("data.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (file_descriptor < 0)
    {
        perror("Error opening file");
        exit(1);
    }

    write(file_descriptor, init_str, strlen(init_str));  // Записываем начальное число в файл

    // Создание и инициализация семафора
    int sem_id = semget(SEM_KEY, 1, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    if (sem_id < 0)
    {
        perror("Error creating semaphore");
        exit(1);
    }

    union semun {   // Определение структуры для управления семафором
        int val;
        struct semid_ds *buf;
        unsigned short *array;
    } sem_union;

    sem_union.val = 0;  // Устанавливаем начальное значение семафора на 0
    semctl(sem_id, 0, SETVAL, sem_union);

    pid = fork();
    if (pid == -1)
    {
        perror("Error forking process");
        exit(1);
    }
    else if (pid == 0)
    {
        struct sembuf sem_op = {0, -1, 0};  // Уменьшение семафора на 1

        while (1)
        {
            semop(sem_id, &sem_op, 1);  // Ожидание увеличения семафора

            char read_buffer[10];
            lseek(file_descriptor, 0, SEEK_SET);
            read(file_descriptor, read_buffer, sizeof(read_buffer));
            printf("Child process read number from file: %s\n", read_buffer);
        }
    }
    else
    {
        while (1)
        {
            int new_number;
            printf("Enter a new number to write to the file: ");
            scanf("%d", &new_number);

            char str[10];
            sprintf(str, "%d", new_number);
            lseek(file_descriptor, 0, SEEK_SET);
            write(file_descriptor, str, strlen(str));

            struct sembuf sem_op = {0, 1, 0};  // Увеличение семафора на 1
            semop(sem_id, &sem_op, 1);  // Разблокировка доступа для дочернего процесса
        }
    }

    close(file_descriptor);

    return 0;
}
