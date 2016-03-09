/*
 * TCP_Client.c
 *
 *  Created on: Mar 4, 2016
 *      Author: viral
 */
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

void error(char * message)
{
	fprintf(stderr,"%s:%s\n",message,strerror(errno));
	exit (1);

}

int main(int argc, char* argv[])
{
	int client_fd;
	struct sockaddr_in serveraddr_TCP;
	char  user_input[1024];
	char  recieve_buff[1024];
	memset(recieve_buff,0,sizeof(recieve_buff));
	memset(user_input,0,sizeof(user_input));
	//FILE * file;
	//file=fopen("input_data.txt","a");
	char input_char;
	int i;

	client_fd=socket(PF_INET,SOCK_STREAM,0);
	if(client_fd<0)
	{
		error("Unable to create socket");
	}
	serveraddr_TCP.sin_family=PF_INET;
	serveraddr_TCP.sin_port=htons(5000);
	serveraddr_TCP.sin_addr.s_addr=inet_addr("127.0.0.1");

	if(connect(client_fd,(struct sockaddr *)&serveraddr_TCP,sizeof(serveraddr_TCP))<0)
	{
		error("Can't Connect to Server");
	}
	//printf("connected to server \n");
	while(1)
	{
		wait();
		if(read(client_fd,recieve_buff,128)<0)
		{
			error("Error in receiving data \n");
		}
		printf("\n Server:");
		printf("%s",recieve_buff);
		printf("\n Client:");
		scanf("%c",&input_char);

		while(input_char !='~')
		{
			printf("testcond \n");
			user_input[i]=input_char;
			i++;
			scanf("%c",&input_char);
		}

//		char * msg= "Thankyou for accepting the connection \n ";
		if(write(client_fd,user_input,sizeof(user_input))<0)
		{
			error("Error in sending the data\n");
		}
		memset(recieve_buff,0,sizeof(recieve_buff));
		memset(user_input,0,sizeof(user_input));
	}
	shutdown(client_fd,SHUT_WR);
	return 0;
}


