#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define SERVER_PORT 8080
#define BUFFER_SIZE 1024


void executeCommand(int clientSocket, const char* command) {
    char buffer[BUFFER_SIZE];
    char tempFile[] = "/tmp/result.txt";

    //execute command and save output to temp file
    sprintf(buffer, "%s > %s", command, tempFile);
    system(buffer);

    //read temp file and send
    int fd = open(tempFile, O_RDONLY);
    int bytesRead;

    memset(buffer, 0, sizeof(buffer));
    while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0) {
        send(clientSocket, buffer, bytesRead, 0);
        // printf("sending")
        memset(buffer, 0, sizeof(buffer));
    }
    close(fd);
    remove(tempFile);
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen;
    char buffer[BUFFER_SIZE];

    //create socket
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    //bind 
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        printf("Binding failed");
        exit(EXIT_FAILURE);
    }

    //listen
    if (listen(serverSocket, 5) == -1) {
        printf("Listening failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", SERVER_PORT);

    while (1) {
        //accept
        clientAddrLen = sizeof(clientAddr);
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        // printf("accepted")
        if (clientSocket == -1) {
            printf("Accepting client connection failed");
            exit(EXIT_FAILURE);
        }

        //recieve command
        memset(buffer, 0, sizeof(buffer));
        recv(clientSocket, buffer, BUFFER_SIZE, 0);
        // printf("rec")

        // printf("stuck1")
        executeCommand(clientSocket, buffer);
        // printf("stuck2")
        close(clientSocket);
    }

    //close the server socket
    close(serverSocket);

    return 0;
}
