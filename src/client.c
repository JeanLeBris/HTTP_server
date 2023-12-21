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

    // if(listen(fdsocket, BACKLOG) != 0){
    //     printf("listening failure: %s\n", strerror(WSAGetLastError()));
    //     exit(EXIT_FAILURE);
    // }

    int serverSocket;
    SOCKADDR_IN serverAdress;
    serverAdress.sin_addr.s_addr = inet_addr("192.168.1.98");
    serverAdress.sin_family = AF_INET;
    serverAdress.sin_port = htons(4148);
    int addrlen = sizeof(serverAdress);
    if((serverSocket = connect(fdsocket, (SOCKADDR *) &serverAdress, addrlen)) != -1){
        char ip[16];
        inet_ntop(AF_INET, &(serverAdress.sin_addr), ip, 16);
        printf("connexion: %s:%i\n", ip, serverAdress.sin_port);
    }

    char buffer[300];
    // send(serverSocket, buffer, 300, 0);
    // int len = read(serverSocket, buffer, 300);
    strcpy(buffer, "Hello World!\r\n");
    write(serverSocket, buffer, strlen(buffer));
    int len = read(fdsocket, buffer, 300);
    printf("len: %i\tbuffer: %s\n", len, buffer);

    WSACleanup();

    return EXIT_SUCCESS;
}