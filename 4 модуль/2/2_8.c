#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h> // Добавляем этот заголовочный файл

void signalHandler(int signal) {
    // Пустая функция обработчика сигнала
}

int main() {
    int num_numbers = 5;
    FILE *file = fopen("numbers.txt", "w");

    srand(getpid());
    int pid = fork();

    if (pid == 0) {
        // Child process
        signal(SIGUSR1, signalHandler);

        while (1) {
            pause();

            FILE *child_file = fopen("numbers.txt", "r");

            int num;
            while (fscanf(child_file, "%d", &num) == 1) {
                printf("Child reading number from file: %d\n", num);
            }

            fclose(child_file);

            // Проверяем, было ли прочитано число -1, признак конца
            if (num == -1) {
                break;
            }

            kill(getppid(), SIGUSR1);
        }
    } else {
        // Parent process
        signal(SIGUSR1, signalHandler);

        for (int i = 0; i < num_numbers; i++) {
            int num = rand() % 100;

            FILE *parent_file = fopen("numbers.txt", "a");
            fprintf(parent_file, "%d\n", num);
            fclose(parent_file);

            printf("Parent writing number to file: %d\n", num);
            kill(pid, SIGUSR1);
            pause();
        }

        // Завершаем дочерний процесс после завершения работы
        FILE *parent_file = fopen("numbers.txt", "a");
        fprintf(parent_file, "-1\n");
        fclose(parent_file);

        // Ожидаем завершения дочернего процесса
        wait(NULL);
    }

    fclose(file);

    return 0;
}
