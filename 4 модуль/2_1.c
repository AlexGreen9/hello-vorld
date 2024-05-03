#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#define BUFFER_SIZE 10

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_integers>\n", argv[0]);
        return 1;
    }

    int numIntegers = atoi(argv[1]);

    int filedes[2];
    if (pipe(filedes) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // дочерний процесс

        close(filedes[0]); // Закрыть чтение конца пайпа


        srand(time(0));
        for (int i = 0; i < numIntegers; i++) {
            int randomNum = rand() % 100;
            write(filedes[1], &randomNum, sizeof(int));
        }

        close(filedes[1]); // Закрыть конец канала записи пайпа

        exit(0);
    } else {
        // родительский процесс

        close(filedes[1]); // Закрыть конец канала записи пайпа

        printf("Received numbers:\n");

        FILE *file = fopen("numbers.txt", "w");
        if (file == NULL) {
            perror("fopen");
            return 1;
        }

        int num;
        while (read(filedes[0], &num, sizeof(int)) > 0) {
            printf("%d\n", num);
            fprintf(file, "%d\n", num);
        }

        fclose(file);

        close(filedes[0]); // Закрыть чтение конца пайпа

        wait(NULL); // Дождитесь завершения дочернего процесса

        return 0;
    }
}
