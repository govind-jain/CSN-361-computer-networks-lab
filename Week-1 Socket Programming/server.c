// Server side C/C++ program to demonstrate Socket
// programming
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080


int main(int argc, char const* argv[]){
    
    int server_fd, valread;
    int new_socket1;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
  
    // Creating socket file descriptor
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    else{
    	printf("Socket created successfully\n");
    }
  
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
  
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    else{
    	printf("Binded successfully\n");
    }
    
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    else{
    	printf("Listening successfully\n");
    }
    
    if ((new_socket1 = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0){
        perror("accept");
        exit(EXIT_FAILURE);
    }
    
    char* hello1 = "Hello client 1 from server";
    char *notRecieved = "Message Not Recieved by Server";
    char *recieved = "Message Recieved by Server";
    
    char buffer[10] = { 0 };
    memset(buffer, 0, sizeof(buffer));
    
    int bytesLeft = sizeof(buffer) - sizeof(char);

    valread = read(new_socket1, buffer, bytesLeft);
    if (valread < 0)
    {
    error("ERROR reading from socket");
    }
    if(valread == 0)
    {
    error("peer shutted down");
    }
	    
    bytesLeft -= valread;
	
    if(bytesLeft == 0 && read(new_socket1, buffer, 1) > 0){
    	send(new_socket1, notRecieved, strlen(notRecieved), 0);
    	
    	char *sz = "Size of buffer is: ";
    	print(typeof(size_of(buffer)));
    	
    	send(new_socket1, sz, strlen(sz), 0);
    }
    else{
    	send(new_socket1, recieved, strlen(recieved), 0);
    }

    printf("%s\n", buffer);

    send(new_socket1, hello1, strlen(hello1), 0);
    printf("Hello message sent\n");
    
    // closing the connected socket
    close(new_socket1);
    
    // closing the listening socket
    shutdown(server_fd, SHUT_RDWR);
    
    return 0;
}