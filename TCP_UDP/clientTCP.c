#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(void) 
{
	
	int socket_desc = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(2000);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	char server_message[2000], client_message[2000];
	
	//send the req to server 
	connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr));
	
	//it'll wait for server to recv()
	client_message[2000] = "Hello from client";
  	server_message[2000] = "Hello from server";
  	
	send(socket_desc, client_message, strlen(client_message),0);

	recv(socket_desc, server_message, sizeof(server_message),0);






}
