#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "network.h"


int InitConnection(networkingData* nData)
{
    printf("WSA");

    if (WSAStartup(MAKEWORD(2, 2), &(nData->wsaData)) != 0)
    {
        printf("Errore WSAStartup\n");
        return 1;
    }

    printf("socket");

    nData->client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (nData->client_socket == INVALID_SOCKET)
    {
        printf("Errore socket: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    printf("Server addr");

    memset(&nData->server_addr, 0, sizeof(nData->server_addr));
    nData->server_addr.sin_family = AF_INET;
    nData->server_addr.sin_port = htons(SERVER_PORT);
    nData->server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    printf("Client data");
    nData->is_running = 1;

    printf("Received thread");

    printf("\nInitConnection: nData=%p &nData=%p is_running=%d\n",
       (void*)nData, (void*)&nData, nData->is_running);

    nData->receive_thread = CreateThread(NULL,0,ReceiveThread,nData,0,&nData->thread_id);

    if (nData->receive_thread == NULL)
    {
        printf("Errore creazione thread ricezione\n");
        closesocket(nData->client_socket);
        WSACleanup();
        return 1;
    }

    return 0;
}

DWORD WINAPI ReceiveThread(LPVOID param)
{
    printf("\nReceiveThread: param=%p\n", param);
    networkingData* data = (networkingData*)param;
    printf("ReceiveThread: data=%p is_running=%d\n", (void*)data, data->is_running);
    char buffer[MAX_BUFFER];
    struct sockaddr_in from_addr;
    int from_addr_len;

    printf("[Receive Thread] start\n");
    from_addr_len = sizeof(from_addr);
    printf("[Receive Thread] is running: %d",data->is_running);

    while (data->is_running)
    {
        printf("ciao_first\n");
        int bytes_received = recvfrom(data->client_socket,buffer,MAX_BUFFER - 1,0,(struct sockaddr*)&from_addr,&from_addr_len);

        if (bytes_received == SOCKET_ERROR)
        {
            int error = WSAGetLastError();
            if (error == WSAETIMEDOUT)
            {
                continue;
            }
            continue;
        }

        buffer[bytes_received] = '\0';
        printf("ciao_last\n");
        //printf("%s\n", buffer);
        //my mini parser (to understand with a clean printf if other players position arrived correctly)
        if (strncmp(buffer, "UDP", 3) == 0)
        {
            int id;
            float x, y;
            if (sscanf(buffer, "UDP:%d,%f,%f", &id, &x, &y) == 3)// at lesson we read that scanf return the num of argument readed from the char buffer
            {
                printf("[PLAYER n. %d]  x = %.2f   y = %.2f\n", id, x, y);// %.2 two digits
            }
        }
        else
        {
            printf("[Other Net Info] %s\n", buffer);// other to printf
        } 
        //.
    }

    printf("[Receive Thread] stop\n");
    return 0;
}


void SendMessage(networkingData* nData, char* message)
{
    sendto(nData->client_socket,
           message,
           strlen(message),
           0,
           (struct sockaddr*)&nData->server_addr,
           sizeof(nData->server_addr));
}

void NetworkCleanUp(networkingData* nData)
{
    nData->is_running = 0;

    WaitForSingleObject(nData->receive_thread, 2000);
    CloseHandle(nData->receive_thread);

    closesocket(nData->client_socket);
    WSACleanup();
}
