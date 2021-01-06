/*
	================CLIENT=UDP===================
*/
#include <cstring>    // sizeof()
#include <iostream>
#include <string>   


#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <unistd.h>    // Close()
#include <arpa/inet.h>
#include <sys/socket.h>

int SIZE {100};	    //Longuer du buffer
int PORT {9600};	// Definition du PORT

void raise_error(char *s)
{
	perror(s);
	exit(1);
}

int main(int argc, char *argv[])
{   
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

    u_int socketfd;
	sockaddr_in udp_server;
    hostent *host;
	char buffer[SIZE];
	char message[SIZE];

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

   	u_int slen=sizeof(udp_server);

	if ( (socketfd=socket(AF_INET, SOCK_DGRAM, 0)) == -1 )
	{
		raise_error("socket");
        return -1; // Sortie
	}
    std::cout <<"Socket créée avec succes!\n\n";

    udp_server.sin_family = AF_INET;
    in_addr udp_addr = *(struct in_addr *)(host->h_addr_list);
    udp_server.sin_addr = udp_addr;
    udp_server.sin_port = htons(PORT);

    if (argv[1] == NULL)
    {
        raise_error("Erreur argv[1]");

        // Fermeture du socket en cas d'erreur
        close(socketfd);
        return 1;
    }
    std::cout << "argv[1] contient\n", argv[1];

    host = gethostbyname(argv[1]);
    if (!host) {
        std::cout << "non trouvee\n",argv[1];

        // Fermeture du socket en cas d'erreur
        close(socketfd);
        exit(EXIT_FAILURE);
    }
    std::cout << "trouvee\n",argv[1];



	while(1)
	{
		std::cout << ("Enter votre message : ");
		std::cin >> message;
		
		//Envoi du message
		if (sendto(socketfd, message, strlen(message) , 0 , (struct sockaddr *) &udp_server, slen)==-1)
		{
			raise_error("sendto()");
            
            // Fermeture du socket en cas d'erreur
            close(socketfd);
		}
		

		memset(buffer,'\0', SIZE);
		// Réception des Données
		if (recvfrom(socketfd, buffer, SIZE, 0, (struct sockaddr *) &udp_server, &slen) == -1)
		{
			raise_error("recvfrom()");

            // Fermeture du socket en cas d'erreur
            close(socketfd);
		}
		

	}

    if (close(socketfd) == -1){
        raise_error("closing");
        return -1;
    }

	close(socketfd); //Bye bye!
	return 0;
}
