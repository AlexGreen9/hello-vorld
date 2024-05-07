#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8888
#define SERVER_IP "127.0.0.1"
#define BUF_SIZE 1024

int main() {
    struct sockaddr_in server_addr;
    int client_sock;
    char buffer[BUF_SIZE];

    // Создание UDP сокета
    if ((client_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Заполнение структуры server_addr
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    while(1) {
        printf("Client: ");
        fgets(buffer, BUF_SIZE, stdin);
        sendto(client_sock, buffer, strlen(buffer), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));

        memset(buffer, '\0', BUF_SIZE);

        // Прием ответа от сервера
        recvfrom(client_sock, buffer, BUF_SIZE, 0, NULL, NULL);
        printf("Server: %s\n", buffer);
    }

    close(client_sock);
    return 0;
}
