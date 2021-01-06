/*
* Code du client
*/
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#include <unistd.h>

#include <string.h>
#define SIZE 100
#define PORT 9600

int main (int argc, char *argv[])
{
    WSADATA WSAData; // variable initialis�e par WSAStartup
    WSAStartup(MAKEWORD(2,0), &WSAData); // indique la version utilis�e, ici 2.0

    /*
    * Variables du client
    *
    * D�clarer ici les variables suivantes :
    * - sockfd le descripteur de socket
    * - structure d�adresse du serveur
    * - pointeur vers la structure descriptive de machine (hostent)
    * - zone de m�moire destin�e � accueillir la cha�ne
    * entr�e au clavier
    * - taille de la cha�ne � envoyer
    */

    SOCKET sockfd;
    struct sockaddr_in tcp_server;
    struct in_addr tcp_addr;
    struct hostent *host;

    char* buffer[SIZE];

    /*
    * Code du client
    *
    * - Ouvrir le socket du client
    * - R�cup�rer l�adresse IP du serveur � partir de son nom
    * donn� en ligne de commande
    * - Remplir la structure d�adresse du serveur
    * - Lire une ligne de l�entr�e standard
    * - Envoyer la cha�ne lue au serveur
    */

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
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

    tcp_server.sin_family = AF_INET;
    tcp_addr = *(struct in_addr *)(host->h_addr);
    tcp_server.sin_addr = tcp_addr;

    tcp_server.sin_port = htons(PORT);

    if(connect(sockfd, (SOCKADDR *)&tcp_server, sizeof(tcp_server)) == SOCKET_ERROR)
    {
        printf("Erreur connect: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    printf("Client connecte au serveur.\n");


    printf("Saisir un message :\n");
    scanf("%20[^\t\n]s", buffer);
    printf("Message a envoyer :\n%s\n\n", buffer);

    if(send(sockfd, buffer, SIZE, 0) == SOCKET_ERROR)
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

    WSACleanup(); // termine l�utilisation

    return 0;
}
