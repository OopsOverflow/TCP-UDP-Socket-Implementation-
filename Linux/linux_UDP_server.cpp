/*
	==================UDP=SERVER=====================
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

int main()
{   
    /*
    * Variables du serveur
    *
    * Déclarer ici les variables suivantes :
    * - sockfd le descripteur de socket
    * - structure d’adresse locale du serveur
    * - structure d’adresse du client
    * - taille de l’adresse du client
    */
   
	struct sockaddr_in udp_server, udp_client;
	
	u_int socketfd, i, slen= sizeof(udp_client) , recv_len;
  
	char buffer[SIZE];
	
	//Création du socket UDP
	if ((socketfd=socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		raise_error("socket");
        return -1;
	}
	

	memset((char *) &udp_server, 0, sizeof(udp_server));
	
	udp_server.sin_family = AF_INET;
	udp_server.sin_port = htons(PORT);
	udp_server.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	//bind socketfd et port
	if( bind(socketfd , (struct sockaddr*)&udp_server, sizeof(udp_server) ) == -1)
	{
		raise_error("bind");

        // Fermeture du socket en cas d'erreur
        close(socketfd);
        return -1;
	}
	
	/*
    * Boucle générale du serveur (infinie)
    */
	while(1)
	{
		std::cout <<("Attente de Réception...");
	
		
		//Réception de Données
		if ((recv_len = recvfrom(socketfd, buffer, SIZE, 0, (struct sockaddr *) &udp_client, &slen)) == -1)
		{
			raise_error("recvfrom()");

            // Fermeture du socket en cas d'erreur
            close(socketfd);
            return -1;
		}
		
		//Données Récues
		std::cout <<"- Message Réçu\n", inet_ntoa(udp_client.sin_addr), ntohs(udp_client.sin_port);
		std::cout <<"Data\n" , buffer;
		
	}
    if (close(socketfd) == -1){
        raise_error("closing");
        return -1;
    }

    //termine l'utilisation
	close(socketfd);
	return 0;
}
