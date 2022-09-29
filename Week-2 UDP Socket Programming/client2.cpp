// Client side implementation of UDP client-server model 
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
    char buffer[MAXLINE];
    struct sockaddr_in servaddr; 
    
    // Creating socket file descriptor 
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){ 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
    
    memset(&servaddr, 0, sizeof(servaddr)); 
        
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
        
    
    char *connectRequest = "I want to connect";
    char *youAreSource  = "You are successfully connected. You will be treated as source";
    char *youAreSink = "You are successfully connected. You will be treated as sink";
    
    socklen_t len;
    ssize_t n;

    sendto(sockfd, (const char *)connectRequest, strlen(connectRequest), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr)); 
    printf("Connection request sent.\n"); 

    while(1){
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &servaddr, &len); 
        
        if(n == -1){
            printf("Message not recieved successfully");
            continue;
        }

        string strRecieved = getMessage(buffer, 0, n, MAXLINE);
        char* messageRecieved = const_cast<char*>(strRecieved.c_str());

        printf("Server : %s\n", messageRecieved);

        if(strcmp(messageRecieved, youAreSource) == 0){
            break;
        }
    }

    //Send random messages
    for(int i=0; i<10; i++){
        string message = "Message-" + to_string(i) + " from client-1";
        char *messageToBeSent = const_cast<char*>(message.c_str());
        sendto(sockfd, (const char *)messageToBeSent, strlen(messageToBeSent), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr)); 
    }
    
    close(sockfd); 
    return 0; 
}