#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(void) 
{
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(2000);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	char server_message[2000], client_message[2000];
	
	
	int socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	
	if (socket_desc < 0){
          printf("[-]Socket error");
          exit(1);
        }
        printf("[+]TCP server socket created.\n");
	
	connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr));
	printf("connected to the server \n");
	      
	//send the req to server and wait for server to recv()
	client_message[2000] = "Hello from client";
  	server_message[2000] = "Hello from server";
  	
	send(socket_desc, client_message, strlen(client_message),0);

	recv(socket_desc, server_message, sizeof(server_message),0);






}
