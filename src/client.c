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

    // create a socket linked to a specific transport service provider
    SOCKET fdsocket = CreateSocket();

    // Specify a transport address and a port for the client
    SOCKADDR_IN sin = CreateClientSinForCli();

    // Associates a local address with a socket
    BindingSocket(&fdsocket, &sin);

    // Specify a transport address and a port for the server
    SOCKADDR_IN serverAdress = CreateServerSin();

    // establish a connexion to a socket
    // int serverSocket = ConnectServerSocket(&fdsocket, &serverAdress);
    ConnectServerSocket(&fdsocket, &serverAdress);

    char buffer[300];
    // send(serverSocket, buffer, 300, 0);
    // int len = read(serverSocket, buffer, 300);
    strcpy(buffer, "Hello World !\r\n");
    // write(serverSocket, buffer, strlen(buffer));
    
    // send data to a socket
    send(fdsocket, buffer, 300, 0);

    // receive data from a socket
    int len = recv(fdsocket, buffer, 300, 0);
    printf("len: %i\nbuffer:\n%s\n", len, buffer);

    // close an existing socket
    closesocket(fdsocket);

    WSACleanup();

    return EXIT_SUCCESS;
}