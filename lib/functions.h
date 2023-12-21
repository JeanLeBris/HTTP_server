#ifndef __FUNCTIONS__

#define __FUNCTIONS__

SOCKET CreateSocket();
SOCKADDR_IN CreateSin();
void BindingSocket(SOCKET *fdsocket, SOCKADDR_IN *sin);
void ListenSocket(SOCKET *fdsocket);
int AcceptClientSocket(SOCKET *fdsocket, SOCKADDR_IN *clientAdress);

#endif