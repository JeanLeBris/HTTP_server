#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "../lib/functions.h"
#include "../lib/config.h"

int main(int argc, char *argv[]){
    config_type config = malloc(sizeof(*config));
    Set_Default_Config(config, argv[0]);
    Load_Config(config);
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2, 0), &WSAData);

    // create a socket linked to a specific transport service provider
    SOCKET fdsocket = CreateSocket();

    // Specify a transport address and a port for the server
    SOCKADDR_IN sin = CreateClientSinForServ();

    // Associates a local address with a socket
    BindingSocket(&fdsocket, &sin);

    // change socket state to listening
    ListenSocket(&fdsocket);

    struct request request_object;
    struct response response_object;
    char buffer[100000];
    // int received_len = -1;
    // int sent_len = -1;

    SOCKADDR_IN clientAdress;
    SOCKET clientSocket;

    while(1){
        // accept an incoming connexion on a socket
        clientSocket = AcceptClientSocket(&fdsocket, &clientAdress);

        // receive data from a socket
        memset(buffer, 0, 100000);
        // received_len = recv(clientSocket, buffer, 2000, 0);
        recv(clientSocket, buffer, 100000, 0);

        ProcessRequestData(&request_object, buffer);

        PrintRequestLog(&request_object, clientAdress);
        // PrintRequest(&request_object);

        ForgeResponseFromRequest(&response_object, &request_object, config);

        memset(buffer, 0, 100000);
        ProcessResponseData(&response_object, buffer);

        PrintResponseLog(&response_object, clientAdress);
        // PrintResponse(&response_object);
        // PrintResponseBuffer(buffer);

        // send data to a socket
        // sent_len = send(clientSocket, buffer, strlen(buffer), 0);
        send(clientSocket, buffer, response_object.total_length, 0);

        // close an existing socket
        closesocket(clientSocket);
        // closesocket(fdsocket);
    }

    WSACleanup();
    free(config);

    return EXIT_SUCCESS;
}