#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(void)
{

  int socket_desc;
  int client_sock; //waits at accept
  
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
  char client_message[2000] = "Hello i am server file, sending client msg";
  char server_message[2000] = "Hello i am server file, sending server msg";
  
  recv(client_sock, client_message, sizeof(client_message), 0);
  send(client_sock, server_message, strlen(server_message), 0);
  


}


