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
// #define SIN_PORT 4148

#define BACKLOG 3

SOCKET CreateSocket(){
    SOCKET fdsocket;
    if((fdsocket = socket(SOCKET_DOMAIN, SOCKET_TYPE, SOCKET_PROTOCOL)) == -1){
        printf("socket creation failure: %s\n", strerror(WSAGetLastError()));
        exit(EXIT_FAILURE);
    }
    // printf("socket: %lld\n", fdsocket);
    return fdsocket;
}

SOCKADDR_IN CreateClientSinForServ(){
    SOCKADDR_IN sin;
    sin.sin_addr.s_addr = INADDR_ANY;   // inet_addr(SIN_ADDR);
    sin.sin_family = SIN_FAMILY;
    sin.sin_port = htons(4149);
    return sin;
}

SOCKADDR_IN CreateClientSinForCli(){
    SOCKADDR_IN sin;
    sin.sin_addr.s_addr = INADDR_ANY;   // inet_addr(SIN_ADDR);
    sin.sin_family = SIN_FAMILY;
    sin.sin_port = htons(4148);
    return sin;
}

SOCKADDR_IN CreateServerSin(){
    SOCKADDR_IN serverAdress;
    serverAdress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAdress.sin_family = AF_INET;
    serverAdress.sin_port = htons(4149);
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

SOCKET AcceptClientSocket(SOCKET *fdsocket, SOCKADDR_IN *clientAdress){
    int clientSocket;
    int addrlen = sizeof(*clientAdress);
    if((clientSocket = accept(*fdsocket, (SOCKADDR *) clientAdress, &addrlen)) != -1){
        char ip[16];
        inet_ntop(AF_INET, &(clientAdress->sin_addr), ip, 16);
        // printf("connexion: %s:%i\n", ip, clientAdress->sin_port);
    }
    return clientSocket;
}

SOCKET ConnectServerSocket(SOCKET *fdsocket, SOCKADDR_IN *serverAdress){
    int serverSocket;
    int addrlen = sizeof(*serverAdress);
    if((serverSocket = connect(*fdsocket, (SOCKADDR *) serverAdress, addrlen)) != -1){
        char ip[16];
        inet_ntop(AF_INET, &(serverAdress->sin_addr), ip, 16);
        printf("connexion: %s:%i\n", ip, serverAdress->sin_port);
    }
    return serverSocket;
}

char *GetRequestValueFromKey(request_t request, char *key_string){
    int id = -1;
    for(int i = 0; i < 30 && strcmp(request->headers_keys[i], "empty_key") != 0; i++){
        if(strcmp(request->headers_keys[i], key_string) == 0){
            id = i;
            break;
        }
    }
    if(id != -1){
        return request->headers_values[id];
    }
    return "";
}

char *GetResponseValueFromKey(response_t response, char *key_string){
    int id = -1;
    for(int i = 0; i < 30 && strcmp(response->headers_keys[i], "empty_key") != 0; i++){
        if(strcmp(response->headers_keys[i], key_string) == 0){
            id = i;
            break;
        }
    }
    if(id != -1){
        return response->headers_values[id];
    }
    return "";
}

request_t ProcessRequestData(request_t request, char *buffer){
    int i = 0;  // incrementor of buffer
    int j = 0;  // incrementor of dictionary
    int k = 0;  // incrementor of strings in keys and values
    int write_in_keys = 1;
    int write_in_values = 0;
    int write_in_content = 0;
    strcpy(request->headers_keys[0], "empty_key");
    strcpy(request->headers_values[0], "empty_value");
    request->body[0] = '\0';
    while(buffer[i] != '\r' && buffer[i+1] != '\n'){
        if(buffer[i] == ' '){
            j++;
            k = 0;
        }
        else{
            if(j == 0){
                request->http_method[k] = buffer[i];
                k++;
                request->http_method[k] = '\0';
            }
            else if(j == 1){
                request->uri[k] = buffer[i];
                k++;
                request->uri[k] = '\0';
            }
            else if(j == 2){
                request->http_version[k] = buffer[i];
                k++;
                request->http_version[k] = '\0';
            }
        }
        i++;
    }
    j = 0;
    k = 0;
    i+=2;
    while(buffer[i] != '\0'){
        if(write_in_content){
            request->body[k] = buffer[i];
            k++;
            request->body[k] = '\0';
        }
        else{
            if(buffer[i] == ':' && buffer[i+1] == ' '){
                write_in_keys = 0;
                write_in_values = 1;
                write_in_content = 0;
                i++;
                k = 0;
            }
            else if(buffer[i] == '\r' && buffer[i+1] == '\n' && buffer[i+2] != '\r' && buffer[i+3] != '\n'){
                write_in_keys = 1;
                write_in_values = 0;
                write_in_content = 0;
                j++;
                i++;
                k = 0;
            }
            else if(buffer[i] == '\r' && buffer[i+1] == '\n' && buffer[i+2] == '\r' && buffer[i+3] == '\n'){
                write_in_keys = 0;
                write_in_values = 0;
                write_in_content = 1;
                j++;
                i+=3;
                k = 0;
            }
            else if(write_in_keys){
                request->headers_keys[j][k] = buffer[i];
                k++;
                request->headers_keys[j][k] = '\0';
            }
            else if(write_in_values){
                request->headers_values[j][k] = buffer[i];
                k++;
                request->headers_values[j][k] = '\0';
            }
        }
        i++;
    }
    request->amount_of_headers = j;
    return request;
}

response_t ForgeResponseFromRequest(response_t response, request_t request, config_type config){
    char line[10000] = "";
    char document[20000] = "";
    FILE *fptr = NULL;
    char file_path[1000] = "";
    char file_path_in_case_of_failure[1000] = "";
    char *get_arguments = NULL;
    int buffer_int = -1;
    int failure_bool = FALSE;
    char *file_extension = NULL;

    if(strcmp(request->uri, "/") == 0){
        strcpy(request->uri, "/index.html");
    }

    strcat(strcat(file_path, config->website_dir), request->uri);
    file_extension = file_path;

    if(strchr(file_path, '?') != NULL){
        get_arguments = strchr(file_path, '?') + 1;
        get_arguments[-1] = '\0';
    }
    if(strchr(file_path, '.') == NULL){
        failure_bool = TRUE;
    }
    else{
        while(strchr(file_extension, '.') != NULL){
            file_extension = strchr(file_extension, '.') + 1;
        }
    }
    if(strcmp(file_extension, "html") == 0){
        strcpy(response->headers_keys[0], "Content-Type");
        strcpy(response->headers_values[0], "text/html; charset=utf-8");
        response->amount_of_headers = 1;
    }
    else if(strcmp(file_extension, "css") == 0){
        strcpy(response->headers_keys[0], "Content-Type");
        strcpy(response->headers_values[0], "text/css; charset=utf-8");
        response->amount_of_headers = 1;
    }
    else if(strcmp(file_extension, "js") == 0){
        strcpy(response->headers_keys[0], "Content-Type");
        strcpy(response->headers_values[0], "text/javascript; charset=utf-8");
        response->amount_of_headers = 1;
    }
    else{
        failure_bool = TRUE;
    }
    fptr = fopen(file_path, "r");
    if(fptr == NULL){
        if(file_extension == file_path){
            strcat(strcat(file_path_in_case_of_failure, file_path), ".html");
            fptr = fopen(file_path_in_case_of_failure, "r");
            if(fptr != NULL){
                failure_bool = FALSE;
            }
        }
        else{
            failure_bool = TRUE;
        }
    }
    strcpy(response->http_version, request->http_version);
    if(failure_bool){
        response->status_code = 404;
        strcpy(response->status_description, "NOT OK");
        response->amount_of_headers = 0;
    }
    else{
        response->status_code = 200;
        strcpy(response->status_description, "OK");
        while(fgets(line, 100, fptr)) {
            strcat(document, line);
        }
        fclose(fptr);
    }

    strcpy(response->body, document);

    return response;
}

char *ProcessResponseData(response_t response, char *buffer){
    char buffer_bis[20000] = "";

    sprintf(buffer_bis, "%s %d %s\n", response->http_version, response->status_code, response->status_description);
    strcat(buffer, buffer_bis);
    for(int i = 0; i < 30 && i < response->amount_of_headers; i++){
        sprintf(buffer_bis, "%s: %s\n", response->headers_keys[i], response->headers_values[i]);
        strcat(buffer, buffer_bis);
    }
    sprintf(buffer_bis, "\n%s", response->body);
    strcat(buffer, buffer_bis);
    
    return buffer;
}

void PrintRequest(request_t request){
    printf("%s %s %s\n", request->http_method, request->uri, request->http_version);
    for(int i = 0; i < 30 && i < request->amount_of_headers; i++){
        printf("%s: %s\n", request->headers_keys[i], request->headers_values[i]);
    }
    printf("\n%s", request->body);
}

void PrintRequestLog(request_t request, SOCKADDR_IN clientAdress){
    char ip[16];
    inet_ntop(AF_INET, &clientAdress.sin_addr, ip, 16);
    printf("REQ %s:%i %s %s len %lld\n", ip, clientAdress.sin_port, request->http_method, request->uri, strlen(request->body));
}

void PrintResponse(response_t response){
    printf("http version : %s\n", response->http_version);
    printf("status code : %d\n", response->status_code);
    printf("status description : %s\n", response->status_description);
    for(int i = 0; i < 30 && i < response->amount_of_headers; i++){
        printf("key : %s\n", response->headers_keys[i]);
        printf("value : %s\n", response->headers_values[i]);
    }
    printf("body :\n%s\n", response->body);
}

void PrintResponseLog(response_t response, SOCKADDR_IN clientAdress){
    char ip[16];
    inet_ntop(AF_INET, &clientAdress.sin_addr, ip, 16);
    printf("ANS %s:%i %d %s len %lld\n", ip, clientAdress.sin_port, response->status_code, response->status_description, strlen(response->body));
}

void PrintResponseBuffer(char *buffer){
    printf(buffer);
}