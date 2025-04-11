#ifndef __FUNCTIONS__

#define __FUNCTIONS__

#include "config.h"

typedef struct request{
    char http_method[10];
    char uri[100];
    char http_version[10];

    int amount_of_headers;
    char headers_keys[30][100];
    char headers_values[30][100];

    char body[20000];
}*request_t;

typedef struct response{
    char http_version[10];
    int status_code;
    char status_description[30];

    int amount_of_headers;
    char headers_keys[30][100];
    char headers_values[30][100];

    char body[20000];
}*response_t;

SOCKET CreateSocket();
SOCKADDR_IN CreateClientSinForCli();
SOCKADDR_IN CreateClientSinForServ();
SOCKADDR_IN CreateServerSin();
void BindingSocket(SOCKET *fdsocket, SOCKADDR_IN *sin);
void ListenSocket(SOCKET *fdsocket);
SOCKET AcceptClientSocket(SOCKET *fdsocket, SOCKADDR_IN *clientAdress);
SOCKET ConnectServerSocket(SOCKET *fdsocket, SOCKADDR_IN *serverAdress);

char *GetRequestValueFromKey(request_t request, char *key_string);
char *GetResponseValueFromKey(response_t response, char *key_string);

request_t ProcessRequestData(request_t request, char *buffer);

response_t ForgeResponseFromRequest(response_t response, request_t request, config_type config);

char *ProcessResponseData(response_t response, char *buffer);

void PrintRequest(request_t request);
void PrintRequestLog(request_t request, SOCKADDR_IN clientAdress);
void PrintResponse(response_t response);
void PrintResponseLog(response_t response, SOCKADDR_IN clientAdress);
void PrintResponseBuffer(char *buffer);

#endif