#ifndef __FUNCTIONS__

#define __FUNCTIONS__

typedef struct http_message{
    char request[10];
    char document[100];
    char version[10];
    char hostIP[50];
    char hostPort[10];
    char connection[20];
    char referer[100];

    char code[10];
    char codeSup[10];
    char date[40];
    char server[20];
    char contentType[100];
    char contentLength[10];
    char expires[40];
    char lastModified[40];

    char message[10000];
}http_message_t;

SOCKET CreateSocket();
SOCKADDR_IN CreateClientSin();
SOCKADDR_IN CreateServerSin();
void BindingSocket(SOCKET *fdsocket, SOCKADDR_IN *sin);
void ListenSocket(SOCKET *fdsocket);
int AcceptClientSocket(SOCKET *fdsocket, SOCKADDR_IN *clientAdress);
int ConnectServerSocket(SOCKET *fdsocket, SOCKADDR_IN *serverAdress);

http_message_t GetData(char buffer[10000]);

#endif