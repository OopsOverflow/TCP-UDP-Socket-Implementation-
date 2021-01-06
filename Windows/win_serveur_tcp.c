/*
* Code du serveur
*/
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#include <string.h>

#include <unistd.h>

#define SIZE 100
#define PORT 9600

int main(int argc, char *argv[])
{
    WSADATA WSAData; // variable initialisée par WSAStartup
    WSAStartup(MAKEWORD(2,0), &WSAData); // indique la version utilisée, ici 2.0

    /*
    * Variables du serveur
    *
    * Déclarer ici les variables suivantes :
    * - sockfd le descripteur de socket
    * - structure d’adresse locale du serveur
    * - structure d’adresse du client
    * - taille de l’adresse du client
    */

    SOCKET sockfd;
    SOCKET client_socket;
    struct sockaddr_in tcp_server;
    struct sockaddr_in tcp_client;
    int size_client = sizeof(tcp_client);

    /*
    * Code du serveur
    *
    * - Ouvrir le socket du serveur
    * - Remplir la structure d’adresse locale du serveur :
    * - la famille d’adresse
    * - l’adresse IP
    * - le port
    * - Spécifier l’adresse locale du socket du serveur
    */

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == INVALID_SOCKET)
    {
        printf("Erreur de creation socket : %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    printf("Creation du socket.\n");

    tcp_server.sin_family = AF_INET;
    tcp_server.sin_addr.s_addr = inet_addr("127.0.0.1");
    tcp_server.sin_port = htons(PORT);

    if(bind(sockfd, (const struct SOCKADDR *) &tcp_server, sizeof(tcp_server)) == SOCKET_ERROR)
    {
        printf("Erreur bind : %d.\n",WSAGetLastError());
        WSACleanup();
        return 1;
    }

    printf("Bind effectue.\n");

    char* buffer[SIZE];

    /*
    * Boucle générale du serveur (infinie)
    */

    if(listen(sockfd, SOMAXCONN) == SOCKET_ERROR)
    {
        printf("Erreur listen : %d.\n",WSAGetLastError());
        WSACleanup();
        return 1;
    }
    printf("Le serveur ecoute.\n");

    printf("En attente du client...\n");

    while (1)
    {
        /*
        * Code de l’éintrieur de la boucle
        */
        client_socket = accept(sockfd, NULL, NULL);
        if(client_socket == INVALID_SOCKET)
        {
            printf("Erreur accept : %d.\n",WSAGetLastError());
            WSACleanup();
            return 1;
        }
        printf("Un client est connecte au serveur.\n");

        if(recv(client_socket, buffer, SIZE, 0) == SOCKET_ERROR)
        {
            printf("Error read : %d\n",WSAGetLastError());
            WSACleanup();
            return 1;
        }
        printf("    - Message recu : %s\n", buffer);

        if (closesocket(client_socket) == SOCKET_ERROR)
        {
            printf("Erreur fermeture socket client : %d\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }
        printf("Fermeture socket client.\n");

    }

    if (closesocket(sockfd) == SOCKET_ERROR)
    {
        printf("Erreur fermeture socket : %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    WSACleanup(); // termine l’utilisation
    return 0;
}
