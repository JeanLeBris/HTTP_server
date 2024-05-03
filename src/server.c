#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "../lib/functions.h"

int main(int argc, char *argv[]){
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2, 0), &WSAData);

    SOCKET fdsocket = CreateSocket();

    SOCKADDR_IN sin = CreateClientSin();

    BindingSocket(&fdsocket, &sin);

    ListenSocket(&fdsocket);

    SOCKADDR_IN clientAdress;
    int clientSocket = AcceptClientSocket(&fdsocket, &clientAdress);

    // char message[2000] = "\0";
    char buffer[10000];
    // char buffer2[2000];
    // int len = _read(clientSocket, buffer, 300);
    // strcpy(buffer, "Hello World!\r\n");
    int len = recv(clientSocket, buffer, 2000, 0);
    printf("len: %i\tbuffer: %s\n", len, buffer);
    http_message_t message = GetData(buffer);
    // Sleep(100);

    // strcpy(buffer, "\0");
    // FILE *fic = fopen("../page.html", "r");
    // if(fic == NULL){
	// 	return 1;
	// }
	// fseek(fic, 0, SEEK_SET);
    // while(!feof(fic)){
	// 	fgets(buffer2, 500, fic);
    //     strcat(buffer, buffer2);
	// }
	// fclose(fic);
    // strcat(message, "HTTP/1.1 200 OK\n");
    // strcat(message, "Date: Thu, 21 Dec 2023 21:05:05 GMT\n");
    // strcat(message, "Server: deeznuts\n");
    // strcat(message, "Last-Modified: Thu, 20 Dec 2023 21:05:05 GMT\n");
    // strcat(message, "ETag: azerty\n");
    // strcat(message, "Accept-Ranges: bytes\n");
    // strcat(message, "Content-Length: 230\n");
    // strcat(message, "Content-Type: text/html\n\n");
    // strcat(message, buffer);

    send(clientSocket, buffer, strlen(buffer), 0);
    // write(clientSocket, "Hello World!", 13);
    // int len = read(clientSocket, buffer, 300);
    closesocket(clientSocket);

    WSACleanup();

    return EXIT_SUCCESS;
}