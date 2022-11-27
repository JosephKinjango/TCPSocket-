 //ServerSide. Project_2
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>


// #define MAXLINE 4096 /*max text line length*/
// #define SERV_PORT 1024 /*port*/
// #define LISTENQ 8 /*maximum number of client connections */

int main (int argc, char * argv[])
{
	int sockfd, newsockfd, portno, n;
	struct sockaddr_in serv_addr, client_addr;

	char buffer[1024];

	socklen_t len;

	if (argc<2)
	{
	printf("No port provided: <filename.c><server_IP_addr><portno>");
	exit(1);
	}

	//creation of the socket
	portno = atoi(argv[1]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	//check if it was created properly
	if (sockfd<0)
	{
	printf("ERROR in openning socket");
		exit(1);
	}

	//preparation of the socket address
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);


	//BIDING 
 	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{	
		printf("ERROR in binding  socket");

	}
	//LISTEN 
 	listen(sockfd, 3);
	
	len = sizeof(client_addr);

	newsockfd = accept(sockfd, (struct sockaddr *) & client_addr, &len);

	if (newsockfd<0)
	{
	printf("ERROR accepting request../");
		exit(1);
	}

	while(1)
	{

		//READING 
		bzero(buffer, 1024);
		n = read(newsockfd, buffer, 1024);
		if (n<0)
		{
			printf("ERROR in reading... ");
				exit(1);
		}

		//WRITING
		printf("\nClient ==> %s", buffer);
		
		bzero(buffer, 1024);


		fgets(buffer, 1024, stdin);
		n = write(newsockfd, buffer, 1024);
		if (n<0)
		{
			printf("ERROR in writing ... ");
				exit(1);
		}
		//END OF CONVERSTION
		if (!strncmp("Goodbye", buffer, 7))
		{
			break;
		}

	}
		close(newsockfd);
		close(sockfd);
	return 0;

}
