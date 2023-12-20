#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
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

SOCKET CreateSocket(){
    SOCKET fdsocket;
    if((fdsocket = socket(SOCKET_DOMAIN, SOCKET_TYPE, SOCKET_PROTOCOL)) == -1){
        printf("socket creation failure: %s\n", strerror(WSAGetLastError()));
        //exit(EXIT_FAILURE);
    }
    return fdsocket;
}

SOCKADDR_IN CreateSin(){
    SOCKADDR_IN sin;
    sin.sin_addr.s_addr = INADDR_ANY;   // inet_addr(SIN_ADDR);
    sin.sin_family = SIN_FAMILY;
    sin.sin_port = htons(SIN_PORT);
    return sin;
}