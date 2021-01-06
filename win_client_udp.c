/*
* Code du client
*/
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#include <string.h>
#define SIZE 100
#define PORT 9600

int main (int argc, char *argv[])
{
    WSADATA WSAData; // variable initialisée par WSAStartup
    WSAStartup(MAKEWORD(2,0), &WSAData); // indique la version utilisée, ici 2.0

    /*
    * Variables du client
    *
    * Déclarer ici les variables suivantes :
    * - sockfd le descripteur de socket
    * - structure d’adresse du serveur
    * - pointeur vers la structure descriptive de machine (hostent)
    * - zone de mémoire destinée à accueillir la chaîne
    * entrée au clavier
    * - taille de la chaîne à envoyer
    */

    SOCKET sockfd;
    struct sockaddr_in udp_server;
    struct in_addr udp_addr;
    struct hostent *host;

    char* buffer[SIZE];

    /*
    * Code du client
    *
    * - Ouvrir le socket du client
    * - Récupérer l’adresse IP du serveur à partir de son nom
    * donné en ligne de commande
    * - Remplir la structure d’adresse du serveur
    * - Lire une ligne de l’entrée standard
    * - Envoyer la chaîne lue au serveur
    */

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd == INVALID_SOCKET)
    {
        printf("Erreur de creation socket : %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    printf("Socket cree avec succes !\n\n");

    if (argv[1] == NULL)
    {
        printf("Erreur argv[1].\n");
        WSACleanup();
        return 1;
    }
    printf("argv[1] contient %s.\n", argv[1]);
    host = gethostbyname(argv[1]);
    if (!host) {
        printf("%s non trouvee\n",argv[1]);
        exit(EXIT_FAILURE);
    }
    printf("%s trouvee\n",argv[1]);

    udp_server.sin_family = AF_INET;
    udp_addr = *(struct in_addr *)(host->h_addr);
    udp_server.sin_addr = udp_addr;
    udp_server.sin_port = htons(PORT);

    printf("Saisir un message :\n");
    scanf("%20[^\t\n]s", buffer);
    printf("Message a envoyer :\n%s\n\n", buffer);

    if(sendto(sockfd, buffer, SIZE, 0, &udp_server, sizeof(udp_server)) == SOCKET_ERROR)
    {
        printf("Erreur envoie socket : %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    if (closesocket(sockfd) == SOCKET_ERROR)
    {
        printf("Erreur fermeture socket : %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    printf("Socket fermee avec succes !\n\n");

    WSACleanup(); // termine l’utilisation

    return 0;
}
