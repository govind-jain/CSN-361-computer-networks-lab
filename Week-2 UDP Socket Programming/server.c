// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>

#define PORT 8080 
#define MAXLINE 1024 

// Driver code
int main(){ 
    
    int sockfd; 
    struct sockaddr_in servaddr, cliaddr; 

    int clientCount = 0;
    int clientLimit = 10;

    struct sockaddr_in sinkAddress;
    int sizeSinkAddress;
    
    // Creating socket file descriptor 
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){ 
        perror("socket creation failed");
        exit(EXIT_FAILURE); 
    }
    else{
    	printf("Socket created successfully\n");
    }
        
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
        
    // Filling server information 
    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT); 
        
    // Bind the socket with the server address 
    if( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    }
    else{
    	printf("Binded successfully\n");
    }

    char buffer[MAXLINE];
    int len, n;

    char *connectRequest = "I want to connect";
    char *youAreSource  = "You are successfully connected. You will be treated as source";
    char *youAreSink = "You are successfully connected. You will be treated as sink";
    char *pleaseConnectFirst = "Please send connection request before sending other messages";

    while(1){
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);

        if(1){

            if(clientCount == clientLimit){
                printf("Maximum client limit crossed");
                break;
            }

            if(clientCount == 0){
                sinkAddress = cliaddr;
                sizeSinkAddress = len;
                sendto(sockfd, (const char *)youAreSink, strlen(youAreSink), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);
            }
            else{
                sendto(sockfd, (const char *)youAreSource, strlen(youAreSource), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len); 
            }

            clientCount++;
        }
        else{
            if(clientCount == 0){
                sendto(sockfd, (const char *)pleaseConnectFirst, strlen(pleaseConnectFirst), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);
            }
            else{
                sendto(sockfd, (const char *)buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *) &sinkAddress, sizeSinkAddress);           
            }
        }
    }

    return 0;
}