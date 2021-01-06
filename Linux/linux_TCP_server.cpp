/*
  ==================================SERVER====================================
*/

#include <cstring>    // sizeof()
#include <iostream>
#include <string>   


#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <unistd.h>    // Close()

int PORT {9600}; // Port Local Du Serveur


int main()
{

    /*
        * Variables du serveur ** Déclarer ici les variables suivantes :
        * *   - sockfd le descripteur de socket
        * *   - structure d’adresse locale du serveur
        * *   - structure d’adresse du client
        * *   - taille de l’adresse du client
    */

    struct sockaddr_in tcp_server;
    struct sockaddr_in tcp_client;

    tcp_server.sin_addr.s_addr = inet_addr("127.0.0.1");
    tcp_server.sin_port = htons(PORT);

    int sockFD = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFD == -1) {
        std::cout << "Erreur de création du socket\n";
        return -1;
    }


    // Bind entre l'adresse et le socket créée
    int bindR = bind(sockFD, (const sockaddr *) &tcp_server, sizeof(tcp_server));
    if (bindR == -1) {
        std::cout << "Erreur au cours du bind\n";
        
        // Fermeture du socket en cas d'erreur
        close(sockFD);
        return -2;
    }


    // Attente de Connection
    int listenR = listen(sockFD, 8);
    if (listenR == -1) {
        std::cout << "Erreur au cours d'attente\n";

        // Fermeture du socket en cas d'erreur
        close(sockFD);
        return -3;
    }

    //Info client
    sockaddr_storage client_addr;
    socklen_t client_addr_size = sizeof(client_addr);

    const std::string reponse = "Hello World";

    /*
        Boucle Infine
    */

    while (1) {

        // on accpete la connection
        int newFD
          = accept(sockFD, (sockaddr *) &client_addr, &client_addr_size);
        if (newFD == -1) {
            std::cout << "Erreur: Connection Impossible.\n";
            continue;
        }
        std::cout << "Un client est connecte au serveur.\n";

        // Envoie des data dans le second param et s longeur dans la 3eme, et renvoie le nombre de bits envoyés
        auto bytes_sent = send(newFD, reponse.data(), reponse.length(), 0);

        // Réception des messages
        if(recvmsg(newFD, (msghdr *) LC_MESSAGES, 256) == -1)
        {
            std::cout << "Erreur de Récpetion\n";
            close(newFD);
            return -1;
        }
        std::cout<<"Message reçu\n";
        close(newFD);
    }

    // Essai de Fermeture du Socket
    if (close(sockFD) == -1){
        std::cout << "Erreur de Fermeture du Socket\n";
        return -1;
    }

    close(sockFD); // Bye Bye!


    return 0;
}
