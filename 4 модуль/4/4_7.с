#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

#define MAX_NUMBERS 10
#define MAX_SETS 5

int* shared_memory;

int generate_random_number() {
    return rand() % 100 + 1; // Генерация случайного числа от 1 до 100
}

int find_min(int* numbers, int size) {
    int min = numbers[0];
    for (int i = 1; i < size; i++) {
        if (numbers[i] < min) {
            min = numbers[i];
        }
    }
    return min;
}

int find_max(int* numbers, int size) {
    int max = numbers[0];
    for (int i = 1; i < size; i++) {
        if (numbers[i] > max) {
            max = numbers[i];
        }
    }
    return max;
}

void sigint_handler(int signum) {
    printf("\nReceived SIGINT\n");
    exit(0);
}

int main() {
    shared_memory = mmap(NULL, sizeof(int) * MAX_NUMBERS, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    signal(SIGINT, sigint_handler);

    pid_t pid;
    int sets_processed = 0;

    for (int i = 0; i < MAX_SETS; i++) {
        pid = fork();

        if (pid == -1) {
            perror("Fork failed");
            exit(1);
        } else if (pid == 0) {
            sleep(1); // Имитация времени выполнения дочернего процесса
            int numbers[MAX_NUMBERS];
            for (int j = 0; j < MAX_NUMBERS; j++) {
                numbers[j] = generate_random_number();
            }

            int min = find_min(numbers, MAX_NUMBERS);
            int max = find_max(numbers, MAX_NUMBERS);

            shared_memory[0] = min;
            shared_memory[1] = max;

            exit(0);
        } else {
            wait(NULL);

            int min = shared_memory[0];
            int max = shared_memory[1];

            printf("Set %d: Min = %d, Max = %d\n", i+1, min, max);

            sets_processed++;
        }
    }

    printf("Total sets processed: %d\n", sets_processed);

    munmap(shared_memory, sizeof(int) * MAX_NUMBERS);

    return 0;
}
