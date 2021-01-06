/*
    =================================CLIENT===================================
*/

#include <cstring>    // sizeof()
#include <iostream>
#include <string>   


#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <unistd.h>    // Close()

int SIZE {100};
int PORT {9600};

int main (int argc, char *argv[])
{
    /*
    * Variables du client
    *
    * Déclarer ici les variables suivantes :
    * - sockFD le descripteur de socket
    * - structure d’adresse du serveur
    * - pointeur vers la structure descriptive de machine (hostent)
    * - zone de mémoire destinée à accueillir la chaîne
    * entrée au clavier
    * - taille de la chaîne à envoyer
    */

    int sockFD;
    struct sockaddr_in tcp_server;
    struct in_addr tcp_addr;
    struct hostent *host;

    char buffer[SIZE];

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

    sockFD = socket(AF_INET, SOCK_STREAM, 0);
    if(sockFD == -1)
    {
        std::cout <<"Erreur de creation socket\n";
        close(sockFD);
        return -1;
    }
    std::cout <<("Socket créée avec succes !\n");

    if (argv[1] == NULL)
    {
        std::cout <<("Erreur: Entrée\n");
        close(sockFD);
        return 1;
    }
    std::cout <<"argv[1] contient\n" << argv[1];
    host = gethostbyname(argv[1]);
    if (!host) {
        std::cout << "non trouvee\n" << argv[1];
        exit(EXIT_FAILURE);
    }
    std::cout <<"host trouvé\n" << argv[1];

    tcp_server.sin_family = AF_INET;
    tcp_addr = *(struct in_addr *)(host->h_addr);
    tcp_server.sin_addr = tcp_addr;

    tcp_server.sin_port = htons(PORT);

    if(connect(sockFD, (sockaddr *)&tcp_server, sizeof(tcp_server)) == -1)
    {
        std::cout <<"Erreur connection \n";
        close(sockFD);
        return 1;
    }
    std::cout <<"Client connecté au serveur.\n";


    std::cout <<"Saisir un message :\n";
    std::cin >> buffer;
    std::cout <<"Message a envoyer :\n" << buffer;

    if(send(sockFD, buffer, SIZE, 0) == -1)
    {
        std::cout <<"Erreur envoie de message\n";
        close(sockFD);
        return 1;
    }

    if (close(sockFD) == -1)
    {
        std::cout <<"Erreur fermeture socket\n";
        return 1;
    }
    
    close(sockFD);
    std::cout <<"Socket fermee avec succes !\n";

    return 0;
}
