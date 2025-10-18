#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define BUFFER_SIZE 1024

int main(void) 
{
	struct sockaddr_in client_addr;
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(2000);
	client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");		char buffer[BUFFER_SIZE] = {"Hello from client"};
	
	int socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	
	if (socket_desc < 0){
          printf("[-]Socket error");
          exit(1);
        }
        printf("[+]TCP server socket created.\n");
	
	connect(socket_desc, (struct sockaddr*)&client_addr, sizeof(client_addr));
	printf("connected to the server \n");
	      
	//send the msg to server
  	
	ssize_t valwrite;
	valwrite = write (socket_desc, buffer, strlen(buffer));
	close(socket_desc);
	return 0;	



}
