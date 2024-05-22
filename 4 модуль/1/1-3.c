#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_ARGS 10

int main() {
    char input[100];
    char* program_name;
    char* arguments[MAX_ARGS];
    int i = 0;
    
    while (1) {
        printf("Введите имя программы и аргументы (через пробел): ");
        fgets(input, sizeof(input), stdin);
        
        // Разбиваем ввод на отдельные слова
        char* token = strtok(input, " \n");
        program_name = token;
        
        // Заполняем массив аргументов программы
        while (token != NULL && i < MAX_ARGS) {
            arguments[i] = token;
            token = strtok(NULL, " \n");
            i++;
        }
        arguments[i] = NULL;
        
        // Выполняем программу
        if (program_name != NULL) {
            if (execvp(program_name, arguments) == -1) {
                perror("Ошибка при выполнении программы");
            }
        } else {
            printf("Некорректный ввод\n");
        }
    }

    return 0;
}
