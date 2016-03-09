/*
 * TCP_Server.c
 *
 *  Created on: Mar 4, 2016
 *      Author: viral
 */

#include<stdio.h> // standard input/output
#include<sys/socket.h> // required for socket system call
#include<arpa/inet.h> // required for internet IP assignment
#include<errno.h> //for getting the error no.
#include<string.h>
#include<stdlib.h> // in here for exit() system call

#define max_client 5 //maximum no. connection allowed in queue

void error(char * message)
{
	fprintf(stderr,"%s:%s\n",message,strerror(errno));
	exit (1);
}

int main()
{
	struct sockaddr_in serveraddr_TCP;
	struct sockaddr_in clientaddr_TCP;
	char user_input[1024];
	char receive_buff[1024];
	// fill the buffer with '0' i.e to empty it
	memset(receive_buff,0,sizeof(receive_buff));
	memset(user_input,0,sizeof(user_input));

	int server_fd, server_accept_fd;
	char input_char;
	int i;

	// creating new socket for communication
	server_fd=socket(PF_INET,SOCK_STREAM,0);
	if(server_fd<0)
	{
		error("Unable to open socket \n");
	}

	/* This line are for assigning address family,port, IP address to structure variable serveradd_TCP
	 structure sin_family,port,addr is included in #include <arpa/inet.h>*/
	serveraddr_TCP.sin_family=PF_INET;
	serveraddr_TCP.sin_port=htons(5000);
	serveraddr_TCP.sin_addr.s_addr=inet_addr("127.0.0.1");

	// binding the above details to the file descriptor,so as to use file descriptor for connection.
	if(bind(server_fd,(struct sockaddr *)&serveraddr_TCP, sizeof(serveraddr_TCP))<0)
	{
		error("Unable to bind to socket \n");
	}

	//for restricting the no. of client trying to connect to server
	if(listen(server_fd,max_client)<0)
	{
		error("Queue is full, can't listen \n");
	}
	printf("Waiting for client to connect \n");
//	while(1)
//	{
		int clientaddr_TCP_size=sizeof(clientaddr_TCP);
		// Accepting connection from client and creating new socked file description
		server_accept_fd=accept(server_fd,(struct sockaddr *)&clientaddr_TCP,&clientaddr_TCP_size);
		if(server_accept_fd<0)
		{
			error("unable to accept connection \n");
		}
		printf("Client connected \n");
		char *message= "Welcome to XaioNet Server \n";

		//Sending data over newly created socket
		if(send(server_accept_fd,message,strlen(message),0)<0)
		{
			error("unable to send the message \n");
		}
	while(1)
	{
		wait();
		//receiving data from client
		if(recv(server_accept_fd,receive_buff,sizeof(receive_buff),0)<0)
		{
			error("Unable to receive data from client \n");
		}
		printf("\n Client:");
		puts(receive_buff);
		printf("\n Server:");
		scanf("%c",&input_char);

		while(input_char !='~')
		{	printf("testcond \n");
			user_input[i]=input_char;
			i++;
			scanf("%c",&input_char);
		}
		if(send(server_accept_fd,user_input,sizeof(user_input),0)<0)
		{
			error("unable to send the message \n");
		}
		memset(receive_buff,0,sizeof(receive_buff));
		memset(user_input,0,sizeof(user_input));
	}
	//closing  socket FD's
	shutdown(server_accept_fd,SHUT_WR);
	close(server_fd);
	return 0;

}
