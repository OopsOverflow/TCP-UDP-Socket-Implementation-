/*
* Code du serveur
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

/* Port local du serveur */
#define PORT 9600






int main(int argc, char *argv[])
{   
    /*
        Déclaration des Variables du Serv
    */
   
    int sockfd;
    //struct in_addr serv_udp;
    struct sockaddr_in servaddr, cliaddr;
    int addrlen = sizeof(servaddr.sin_addr);
    int cliaddr_size = sizeof(cliaddr.sin_addr);
    char buffer[20];


    /* 
        Remplissage Des ID Serv
    */

    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = PORT;
    




    int domain = PF_INET;
    int type = SOCK_DGRAM;
    int protocol = 0; 


    sockfd = socket(domain, type, protocol);     //Ouvrir le socket du serveur



    while (1) 
    {
        int bind(sockfd, &servaddr, sizeof(servaddr));
        int recv(int sockfd, char *buf, int len, int flags);
	n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len); 
    }
return 0;
}
