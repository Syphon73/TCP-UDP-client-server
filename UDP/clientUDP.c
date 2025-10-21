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
	client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");		int client_struct_length = sizeof(client_addr);       
	char buffer[BUFFER_SIZE] = {};
	
	int socket_desc = socket(AF_INET, SOCK_DGRAM, 0);
	
	if (socket_desc < 0){
          printf("[-]Socket error");
          exit(1);
        }
        printf("TCP server socket created.\n");
	

	memset(buffer,0,BUFFER_SIZE);
	char user_input[BUFFER_SIZE];
	printf("Client: ");
	fgets(user_input,BUFFER_SIZE,stdin);
	strcpy(buffer,user_input);
	
	//////////send mdg to server//////
	if(sendto(socket_desc, buffer, BUFFER_SIZE, 0,
         (struct sockaddr*)&client_addr, sizeof(client_addr)) < 0){
        printf("Unable to send message\n");
        return -1;
    }
	memset(buffer,0,BUFFER_SIZE);

	/////////////recieve server reply///////
	if(recvfrom(socket_desc, buffer, BUFFER_SIZE, 0,
         (struct sockaddr*)&client_addr, &client_struct_length) < 0){
        printf("Error while receiving server's msg\n");
        return -1;
    }
    
    printf("Server's response: %s\n", buffer);	

	close(socket_desc);
	return 0;	




}
