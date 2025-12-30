#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define MAX_BUFFER 1024
#define PORT 8080
#define MAX_CLIENTS 10
#define MAX_NAME_LEN 32

typedef struct {
    struct sockaddr_in address;   // contiene ip e porta del client
    char name[MAX_NAME_LEN];
    int active;                  // 1 = active, 0 = disconnected
    float x;
    float y;
} ClientInfo;

ClientInfo clients[MAX_CLIENTS];
int client_count;   

  int find_or_add_client(struct sockaddr_in client_address)
{
    int i;

    // cerchiamo se esiste il client
    for (i = 0; i < client_count; i++)
    {
        if (clients[i].address.sin_addr.s_addr == client_address.sin_addr.s_addr &&
            clients[i].address.sin_port == client_address.sin_port)
        {
            return i;
        }
    }

    // se non esiste, vediamo se possiamo aggiungerlo
    if (client_count >= MAX_CLIENTS)
    {
        printf("ERRORE: Troppi client");
        return -1;
    }

    // possiamo effettivamente aggiungere un client
    clients[client_count].address = client_address;
    clients[client_count].active = 1;

    sprintf(clients[client_count].name, "client%d", client_count + 1);

    printf("Nuovo client: %s %s:%d\n",
           clients[client_count].name,
           inet_ntoa(client_address.sin_addr),
           ntohs(client_address.sin_port));

    client_count++;
    return client_count - 1;
}

void broadcast_message(SOCKET sock, int sender_index, char* message)
{
    char full_message[MAX_BUFFER];
    sprintf(full_message, "%s", message);

    printf("Broadcast: %s\n", full_message);

    for (int i = 0; i < client_count; i++)
    {
        if (i == sender_index || !clients[i].active)
            continue;

        sendto(sock,
               full_message,
               strlen(full_message),
               0,
               (struct sockaddr*)&clients[i].address,
               sizeof(clients[i].address));
    }
}

int main()
{
    WSADATA wsaData;
    SOCKET server_socket;
    struct sockaddr_in server_addr, client_addr;
    int client_addr_len;
    char buffer[MAX_BUFFER];
    int bytes_received;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("Errore WSAStartup");
        return 1;
    }

    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket == INVALID_SOCKET)
    {
        printf("Errore inizializzazione socket");
        WSACleanup();
        return 1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket,
             (struct sockaddr*)&server_addr,
             sizeof(server_addr)) == SOCKET_ERROR)
    {
        printf("Errore di bind: %d\n", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }
    printf("Server avviato");

    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        clients[i].active = 0;
    }

    client_addr_len = sizeof(client_addr);

    while (1)
    {
        // attendo messaggio da client
        bytes_received = recvfrom(server_socket,
                                buffer,
                                MAX_BUFFER - 1,
                                0,
                                (struct sockaddr*)&client_addr,
                                &client_addr_len);

        if (bytes_received == SOCKET_ERROR)
        {
            printf("Errore recvfrom: %d\n", WSAGetLastError());
            continue;
        }

        buffer[bytes_received] = '\0';

        // messaggio arrivato come stringa
        int client_index = find_or_add_client(client_addr);

        if (client_index == -1)
        {
            char* error_message = "Server pieno";
            sendto(server_socket,
                error_message,
                strlen(error_message),
                0,
                (struct sockaddr*)&client_addr,
                client_addr_len);
            continue;
        }

        // stampo info su messaggio
        // printf("[%s] %s", clients[client_index].name, buffer);
   


        /*
        NEW: New player connected
        UDP: player update
    */

        if (strncmp(buffer, "NEW", 3) == 0)
        {
            char* message = "ACK";
            sendto(server_socket,
                message,
                strlen(message),
                0,
                (struct sockaddr*)&client_addr,
                client_addr_len);
        }
        else if (strncmp(buffer, "UDP", 3) == 0)
        {
            // UDP: posx, posy
            float x, y;
            sscanf(buffer, "UDP:%f,%f", &x, &y);
            printf("%f %f\n", x, y);

            clients[client_index].x = x;
            clients[client_index].y = y;
            //separate buffer for the response:
            char out[MAX_BUFFER];
            snprintf(out, sizeof(out), "UDP:%d,%f,%f",client_index,x,y);
            broadcast_message(server_socket, client_index, out);
        }
    }
    closesocket(server_socket);
    WSACleanup();

    return 0;
}