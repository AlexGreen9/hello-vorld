#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>

#define PORT 1234

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server, client;
    char buffer[1024];
    fd_set readfds;
    int max_fd;
    
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);
    
    if (bind(server_fd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }
    
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    
    printf("Server listening on port %d\n", PORT);
    
    while (1) {
        FD_ZERO(&readfds);
        FD_SET(server_fd, &readfds);
        max_fd = server_fd;
        
        if (select(max_fd + 1, &readfds, NULL, NULL, NULL) < 0) {
            perror("Select error");
            exit(EXIT_FAILURE);
        }
        
        if (FD_ISSET(server_fd, &readfds)) {
            socklen_t client_len = sizeof(client);
            client_fd = accept(server_fd, (struct sockaddr *)&client, &client_len);
            if (client_fd < 0) {
                perror("Accept failed");
                exit(EXIT_FAILURE);
            }
            
            int n = read(client_fd, buffer, sizeof(buffer));
            if (n < 0) {
                perror("Read error");
                exit(EXIT_FAILURE);
            }
            buffer[n] = 0;
            
            int num1, num2;
            char operation;
            sscanf(buffer, "%d %c %d", &num1, &operation, &num2);
            
            int result;
            switch (operation) {
                case '+':
                    result = num1 + num2;
                    break;
                case '-':
                    result = num1 - num2;
                    break;
                case '*':
                    result = num1 * num2;
                    break;
                case '/':
                    if (num2 == 0) {
                        result = 0; // Деление на ноль
                    } else {
                        result = num1 / num2;
                    }
                    break;
                default:
                    result = 0;
                    break;
            }
            
            sprintf(buffer, "Result: %d\n", result);
            write(client_fd, buffer, strlen(buffer));
            close(client_fd);
        }
    }
    
    close(server_fd);
    
    return 0;
}
