#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define BUFFER_SIZE 1024 //keep a temporary place to store msgs

int main(void)
{

  int socket_desc;
  int client_sock; //waits at accept
  char buffer[BUFFER_SIZE] = {0};
  char req_buffer[BUFFER_SIZE] = {0};  
  //server keeps address of server & client in server_addr
  struct sockaddr_in server_addr, client_addr;
  
  
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(2000); //local PORT
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //local IP
  
  ///////////////creating a AF_INET (ipv4) internet protocol. STOCK_STEAM = TCP connections. 0 = choose any appropriate protocol
  socket_desc = socket(AF_INET, SOCK_STREAM, 0);
  
  //check socket connection
  if (socket_desc == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created...\n"); 
  
  /////////////////////bind assigns a local port address to the socket
  int n = bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr));
  
  //check binding
  if (n != 0) { 
      printf("socket bind failed...\n"); 
      exit(0); 
  } 
  else
      printf("Socket successfully binded...\n"); 
  
  ///////////////////////listen to req
  listen(socket_desc, 1);
  
  //check listen
  if(listen(socket_desc, 1) < 0){
      printf("Error while listening\n");
      return -1;
  }
  printf("\nListening for incoming connections.....\n");
  
  
  //wait at accept until client connects
  int client_size = sizeof(client_addr);
  client_sock = accept(socket_desc, (struct sockaddr*)&client_addr, &client_size);
  
  if (client_sock < 0){
    printf("Can't accept\n");
    return -1;
  }
  printf("Client connected at IP: %s and port: %i\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
  
  //wait at recieve
  //read data from client and print it
  //declare a signed variable for number of bytes to read
  ssize_t valread;
  ssize_t valwrite;

 
  while(1){
	
	char user_input[BUFFER_SIZE];
	printf("Server: ");
	fgets(user_input,BUFFER_SIZE,stdin);
	valwrite = write(socket_desc,buffer,strlen(buffer));
	//memset(buffer,0,sizeof(buffer));
	//printf("Client's input %s",buffer);
	//valread = read(client_sock, buffer, BUFFER_SIZE);

	//memset(buffer, 0, sizeof(buffer));

	
  
  }
  close(socket_desc);
  return 0;


}


