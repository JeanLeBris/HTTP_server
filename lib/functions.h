#ifndef __FUNCTIONS__

#define __FUNCTIONS__

SOCKET CreateSocket();
SOCKADDR_IN CreateClientSin();
SOCKADDR_IN CreateServerSin();
void BindingSocket(SOCKET *fdsocket, SOCKADDR_IN *sin);
void ListenSocket(SOCKET *fdsocket);
int AcceptClientSocket(SOCKET *fdsocket, SOCKADDR_IN *clientAdress);
int ConnectServerSocket(SOCKET *fdsocket, SOCKADDR_IN *serverAdress);

#endif