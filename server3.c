#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <unistd.h>

int main(){
  
  char serverMessage[256] = "You are now connected to the server throuch TCP/IP \n";

   int socketDescriptor = socket(AF_INET,SOCK_STREAM,0);
  
  struct sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(9002);
  serverAddress.sin_addr.s_addr = INADDR_ANY;

  bind(socketDescriptor,(struct sockaddr*) &serverAddress,sizeof(serverAddress));
  printf("Server is running...");

  listen(socketDescriptor,5);

  int client_socket = accept(socketDescriptor, NULL, NULL);
  
  send(client_socket,serverMessage,sizeof(serverMessage),0);

  close(socketDescriptor);
    return 0;
}
