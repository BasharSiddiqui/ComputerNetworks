#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];

    //create socket
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("socket creation failed");
        exit(EXIT_FAILURE);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);


    //connect to the server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        printf("connection failed");
        exit(EXIT_FAILURE);
    }

    //get command
    printf("Enter a command: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    
    //ssend command to server
    send(clientSocket, buffer, strlen(buffer), 0);

    //receive and display results from server
    memset(buffer, 0, sizeof(buffer));
    while (recv(clientSocket, buffer, BUFFER_SIZE, 0) > 0) {
        printf("Server response: %s\n", buffer);
        memset(buffer, 0, sizeof(buffer));
    }

    //close the socket
    close(clientSocket);
    return 0;
}
