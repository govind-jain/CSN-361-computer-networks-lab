// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <bits/stdc++.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>

#define PORT 8080 
#define MAXLINE 1024

using namespace std;

string getMessage(char* buffer, int st, int en, int lim){

    en = min(en, lim);

    string res = "";

    for(int i=st; i<en; i++){
        res += buffer[i];
    }

    return res;
}

// Driver code
int main(){ 
    
    int sockfd; 
    struct sockaddr_in servaddr, cliaddr; 

    int clientCount = 0;
    int clientLimit = 10;

    struct sockaddr_in sinkAddress;
    socklen_t sizeSinkAddress;
    
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
    socklen_t len;
    ssize_t n;

    char* connectRequest = "I want to connect";
    char* youAreSource  = "You are successfully connected. You will be treated as source";
    char* youAreSink = "You are successfully connected. You will be treated as sink";
    char* pleaseConnectFirst = "Please send connection request before sending other messages";

    int idx = 0;
    int lim;

    while(true){

        n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &cliaddr, &len);

        if(n == -1){
            printf("Message not recieved successfully");
            continue;
        }
        
        string strRecieved = getMessage(buffer, 0, 0 + n, MAXLINE);
        char* messageRecieved = const_cast<char*>(strRecieved.c_str());

        idx += n;

        if(strcmp(messageRecieved, connectRequest) == 0){

            if(clientCount == clientLimit){
                printf("Maximum client limit crossed");
                break;
            }

            clientCount++;

            if(clientCount == 1){
                sinkAddress = cliaddr;
                sizeSinkAddress = len;
                sendto(sockfd, (const char *)youAreSink, strlen(youAreSink), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);
                cout<<("Client-" + to_string(clientCount) + " is added. It will be treated as sink.")<<endl;
            }
            else{
                sendto(sockfd, (const char *)youAreSource, strlen(youAreSource), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len); 
                cout<<("Client-" + to_string(clientCount) + " is added. It will be treated as source.")<<endl;
            }
        }
        else{
            if(clientCount == 0){
                sendto(sockfd, (const char *)pleaseConnectFirst, strlen(pleaseConnectFirst), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);
            }
            else{
                sendto(sockfd, (const char *)messageRecieved, strlen(messageRecieved), MSG_CONFIRM, (const struct sockaddr *) &sinkAddress, sizeSinkAddress);           
            }
        }
    }

    close(sockfd);
    return 0;
}