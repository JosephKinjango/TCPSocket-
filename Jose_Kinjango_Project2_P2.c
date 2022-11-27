//ClientSide. Project_2
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char * argv[])
{
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;

	char buffer[1024];

	//socklen_t len;

	if (argc<3)
	{
	printf("No port provided: <filename.c><server_IP_addr><portno>");
	exit(1);
	}

	//creation of the socket
	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	//check if it was created properly
	if (sockfd<0)
	{
	printf("ERROR in openning socket");
		exit(1);
	}

	//preparation of the socket address
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);

	//Connecting with the server  
 	if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("ERROR Connection failed");
			exit(1);
	}
	
	while(1)
	{
		
		bzero(buffer, 1024);

		fgets(buffer, 1024, stdin);
		n = write(sockfd, buffer, strlen(buffer));
		if (n<0)
		{
			printf("ERROR in writing ... ");
				exit(1);
		}

		//READING 
		bzero(buffer, 1024);

		n = read(sockfd, buffer, 1024);
		if (n<0)
		{
			printf("ERROR in reading... ");
				exit(1);
		}

		//WRITING
		printf("\nServer ==> %s", buffer);


		//END OF CONVERSTION
		if (!strncmp("Goodbye", buffer, 7))
		{
			break;
		}

	}
		close(sockfd);
	return 0;

}




