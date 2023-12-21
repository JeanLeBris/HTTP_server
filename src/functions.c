#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "../lib/functions.h"

#define SOCKET_DOMAIN AF_INET
/*
    AF_LOCAL
    AF_INET
    AF_INET6
*/
#define SOCKET_TYPE SOCK_STREAM
/*
    SOCK_STREAM
    SOCK_DGRAM
*/
#define SOCKET_PROTOCOL 0

#define SIN_ADDR INADDR_ANY // "127.0.0.1"
#define SIN_FAMILY AF_INET
#define SIN_PORT 4148

#define BACKLOG 3

SOCKET CreateSocket(){
    SOCKET fdsocket;
    if((fdsocket = socket(SOCKET_DOMAIN, SOCKET_TYPE, SOCKET_PROTOCOL)) == -1){
        printf("socket creation failure: %s\n", strerror(WSAGetLastError()));
        exit(EXIT_FAILURE);
    }
    printf("socket: %lld\n", fdsocket);
    return fdsocket;
}

SOCKADDR_IN CreateClientSin(){
    SOCKADDR_IN sin;
    sin.sin_addr.s_addr = INADDR_ANY;   // inet_addr(SIN_ADDR);
    sin.sin_family = SIN_FAMILY;
    sin.sin_port = htons(SIN_PORT);
    return sin;
}

SOCKADDR_IN CreateServerSin(){
    SOCKADDR_IN serverAdress;
    serverAdress.sin_addr.s_addr = inet_addr("192.168.1.98");
    serverAdress.sin_family = AF_INET;
    serverAdress.sin_port = htons(4148);
    return serverAdress;
}

void BindingSocket(SOCKET *fdsocket, SOCKADDR_IN *sin){
    if(bind(*fdsocket, (SOCKADDR *) sin, sizeof(*sin)) != 0){
        printf("binding failure: %s\n", strerror(WSAGetLastError()));
        exit(EXIT_FAILURE);
    }
}

void ListenSocket(SOCKET *fdsocket){
    if(listen(*fdsocket, BACKLOG) != 0){
        printf("listening failure: %s\n", strerror(WSAGetLastError()));
        exit(EXIT_FAILURE);
    }
}

int AcceptClientSocket(SOCKET *fdsocket, SOCKADDR_IN *clientAdress){
    int clientSocket;
    int addrlen = sizeof(*clientAdress);
    if((clientSocket = accept(*fdsocket, (SOCKADDR *) clientAdress, &addrlen)) != -1){
        char ip[16];
        inet_ntop(AF_INET, &(clientAdress->sin_addr), ip, 16);
        printf("connexion: %s:%i\n", ip, clientAdress->sin_port);
    }
    return clientSocket;
}

int ConnectServerSocket(SOCKET *fdsocket, SOCKADDR_IN *serverAdress){
    int serverSocket;
    int addrlen = sizeof(*serverAdress);
    if((serverSocket = connect(*fdsocket, (SOCKADDR *) serverAdress, addrlen)) != -1){
        char ip[16];
        inet_ntop(AF_INET, &(serverAdress->sin_addr), ip, 16);
        printf("connexion: %s:%i\n", ip, serverAdress->sin_port);
    }
    return serverSocket;
}