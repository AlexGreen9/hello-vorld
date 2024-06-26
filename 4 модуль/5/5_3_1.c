#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t sockaddr_len = sizeof(struct sockaddr_in);
    int port = 8080;
    
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Error creating socket");
        exit(1);
    }
    
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port);
    
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Error binding socket");
        exit(1);
    }
    
    listen(server_socket, 5);
    printf("Server is listening on port %d\n", port);
    
    client_socket = accept(server_socket, (struct sockaddr *)&client_address, &sockaddr_len);
    if (client_socket < 0) {
        perror("Error accepting client connection");
        exit(1);
    }
    
    int num1, num2, result;
    char operation[10];
    
    read(client_socket, &num1, sizeof(num1));
    read(client_socket, &num2, sizeof(num2));
    read(client_socket, operation, sizeof(operation));
    
    if (strcmp(operation, "difference") == 0) {
        result = num1 - num2;
    } else if (strcmp(operation, "product") == 0) {
        result = num1 * num2;
    } else if (strcmp(operation, "quotient") == 0) {
        if (num2 == 0) {
            result = -1; // indicate division by zero
        } else {
            result = num1 / num2;
        }
    } else {
        result = -2; // indicate unknown operation
    }
    
    write(client_socket, &result, sizeof(result));
    
    close(client_socket);
    close(server_socket);
    
    return 0;
}
