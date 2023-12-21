#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "../lib/functions.h"

#define BACKLOG 3

int main(int argc, char *argv[]){
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2, 0), &WSAData);

    SOCKET fdsocket = CreateSocket();
    printf("socket: %lld\n", fdsocket);

    SOCKADDR_IN sin = CreateSin();
    // printf("sin: %d\n", sin);

    if(bind(fdsocket, (SOCKADDR *) &sin, sizeof(sin)) != 0){
        printf("binding failure: %s\n", strerror(WSAGetLastError()));
        exit(EXIT_FAILURE);
    }

    if(listen(fdsocket, BACKLOG) != 0){
        printf("listening failure: %s\n", strerror(WSAGetLastError()));
        exit(EXIT_FAILURE);
    }

    int clientSocket;
    SOCKADDR_IN clientAdress;
    int addrlen = sizeof(clientAdress);
    if((clientSocket = accept(fdsocket, (SOCKADDR *) &clientAdress, &addrlen)) != -1){
        char ip[16];
        inet_ntop(AF_INET, &(clientAdress.sin_addr), ip, 16);
        printf("connexion: %s:%i\n", ip, clientAdress.sin_port);
    }

    char buffer[300];
    int len = read(clientSocket, buffer, 300);
    send(clientSocket, buffer, 300, 0);
    // write(clientSocket, "Hello World!", 13);
    // int len = read(clientSocket, buffer, 300);
    printf("len: %i\tbuffer: %s\n", len, buffer);

    WSACleanup();

    return EXIT_SUCCESS;
}