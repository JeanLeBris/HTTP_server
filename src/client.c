#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "../lib/functions.h"

// #define BACKLOG 3

int main(int argc, char *argv[]){
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2, 0), &WSAData);

    SOCKET fdsocket = CreateSocket();

    SOCKADDR_IN sin = CreateClientSin();

    BindingSocket(&fdsocket, &sin);

    SOCKADDR_IN serverAdress = CreateServerSin();
    int serverSocket = ConnectServerSocket(&fdsocket, &serverAdress);

    char buffer[300];
    // send(serverSocket, buffer, 300, 0);
    // int len = read(serverSocket, buffer, 300);
    strcpy(buffer, "Hello World!\r\n");
    // write(serverSocket, buffer, strlen(buffer));
    send(fdsocket, buffer, 300, 0);
    int len = recv(fdsocket, buffer, 300, 0);
    printf("len: %i\tbuffer: %s\n", len, buffer);
    closesocket(fdsocket);

    WSACleanup();

    return EXIT_SUCCESS;
}