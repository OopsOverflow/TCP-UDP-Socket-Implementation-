/*
* Code du serveur
*/
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#include <string.h>

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
    struct sockaddr_in udp_server;
    struct sockaddr_in udp_client;
    int size_client = sizeof(udp_client);

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

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd == INVALID_SOCKET)
    {
        printf("Erreur de creation socket : %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    printf("Creation du socket.\n");

    udp_server.sin_family = AF_INET;
    udp_server.sin_addr.s_addr = inet_addr("127.0.0.1");
    udp_server.sin_port = htons(PORT);

    if(bind(sockfd, (const struct SOCKADDR *) &udp_server, sizeof(udp_server)) == SOCKET_ERROR)
    {
        printf("Erreur bind : %d.\n",WSAGetLastError());
        WSACleanup();
        return 1;
    }

    printf("Bind effectue.\n");

    char* buffer[SIZE];
    printf("En attente du client...\n");
    /*
    * Boucle générale du serveur (infinie)
    */

    while (1)
    {
        /*
        * Code de l’éintrieur de la boucle
        */

        if(recvfrom(sockfd, buffer, SIZE, 0,(SOCKADDR *)  &udp_client, &size_client) != SOCKET_ERROR)
        {
            write(sockfd, buffer, SIZE);
            printf("    - Message recu : %s\n", buffer);
        }
    }

    WSACleanup(); // termine l’utilisation
    return 0;
}
