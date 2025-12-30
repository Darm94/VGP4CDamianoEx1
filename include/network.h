#ifndef NETWORK_H
#define NETWORK_H
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define VC_EXTRALEAN
#define NOGDI
#define NOUSER


#include <winsock2.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

#define MAX_BUFFER 1024
#define SERVER_PORT 8080
#define SERVER_IP "127.0.0.1"   // localhost

typedef struct networkingData
{
    WSADATA wsaData;
    SOCKET client_socket;
    struct sockaddr_in server_addr;
    int is_running;
    HANDLE receive_thread;
    DWORD thread_id;
} networkingData;

DWORD WINAPI ReceiveThread(LPVOID param);

int InitConnection(networkingData* nData);
void SendMessage(networkingData* nData, char* message);
void NetworkCleanUp(networkingData* nData);

#endif

