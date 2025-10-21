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
  memset(buffer,0,BUFFER_SIZE); 
 
  //server keeps address of server & client in server_addr
  struct sockaddr_in server_addr, client_addr;
  int client_struct_length = sizeof(client_addr);
  
  
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(2000); //local PORT
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //local IP
  
  ///////////////creating a AF_INET (ipv4) internet protocol. STOCK_DGRAM = UDP connections. 0 = choose any appropriate protocol
  socket_desc = socket(AF_INET, SOCK_DGRAM, 0);
  
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
  printf("Listening for incoming messages...\n\n");  
 

  /////////recieve client's msg///////////////////
  if (recvfrom(socket_desc, buffer, sizeof(buffer), 0,
         (struct sockaddr*)&client_addr, &client_struct_length) < 0){
        printf("Couldn't receive\n");
        return -1;
    }
    printf("Received message from IP: %s and port: %i\n",
           inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    
    printf("Msg from client: %s\n", buffer); 
    //////////send client response///////
   
    memset(buffer,0,BUFFER_SIZE);
    char user_input[BUFFER_SIZE];
    printf("Your reply: ");
    fgets(user_input,BUFFER_SIZE,stdin);
    strcpy(buffer,user_input);

    if (sendto(socket_desc, buffer, BUFFER_SIZE, 0,
         (struct sockaddr*)&client_addr, sizeof(client_addr)) < 0){
        printf("Can't send\n");
        return -1;
    }
  close(socket_desc);
  return 0;


}
