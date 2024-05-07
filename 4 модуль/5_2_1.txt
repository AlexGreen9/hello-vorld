#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8888
#define BUF_SIZE 1024

int main() {
    struct sockaddr_in server_addr, client_addr;
    int server_sock, client_sock, len, addr_len;
    char buffer[BUF_SIZE];
    
    // Создание UDP сокета
    if ((server_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Заполнение структуры server_addr
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Привязка сокета к порту
    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    printf("Server started. Waiting for messages...\n");

    addr_len = sizeof(client_addr);
    while(1) {
        memset(buffer, '\0', BUF_SIZE);
        
        // Прием сообщения от клиента
        len = recvfrom(server_sock, buffer, BUF_SIZE, 0, (struct sockaddr*)&client_addr, &addr_len);
        
        buffer[len] = '\0';
        printf("Client: %s\n", buffer);

        // Отправка ответа клиенту
        printf("Server: ");
        fgets(buffer, BUF_SIZE, stdin);
        sendto(server_sock, buffer, strlen(buffer), 0, (struct sockaddr*)&client_addr, addr_len);
    }

    close(server_sock);
    return 0;
}
