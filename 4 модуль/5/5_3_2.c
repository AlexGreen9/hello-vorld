
//TCP client program
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    int client_socket;
    struct sockaddr_in server_address;
    int port = 8080;
    
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Error creating socket");
        exit(1);
    }
    
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(port);
    
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Error connecting to server");
        exit(1);
    }
    
    int num1, num2, result;
    char operation[10];
    
    printf("Enter first number: ");
    scanf("%d", &num1);
    printf("Enter second number: ");
    scanf("%d", &num2);
    printf("Enter operation (difference, product, quotient): ");
    scanf("%s", operation);
    
    write(client_socket, &num1, sizeof(num1));
    write(client_socket, &num2, sizeof(num2));
    write(client_socket, operation, sizeof(operation));
    
    read(client_socket, &result, sizeof(result));
    
    if (result == -1) {
        printf("Error: Division by zero\n");
    } else if (result == -2) {
        printf("Error: Unknown operation\n");
    } else {
        printf("Result: %d\n", result);
    }
    
    close(client_socket);
    
    return 0;
}
