
#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h> 

#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 
#define SIZE 1024

void func(int sockfd, FILE *fp) 
{ 
    char buff[MAX]; 
    int n;
   
    for (;;) { 
        bzero(buff, sizeof(buff)); 
        printf("Enter the string : "); 
        n = 0; 
        while ((buff[n++] = getchar()) != '\n') 
            ; 
        write(sockfd, buff, sizeof(buff)); 
        bzero(buff, sizeof(buff)); 
        read(sockfd, buff, sizeof(buff)); 
        printf("From Server : %s", buff); 
	if ((strncmp(buff, "file", 4)) == 0) {
	    printf("server is requesting a file");
	    
	    send_file(fp, sockfd);
	    printf("[+]File data sent successfully.\n");
	    
	    printf("[+]Closing the connection.\n");
	    close(sockfd);

	    if (fp == NULL) {
	        perror("[-]Error in reading file.");
		exit(1);
       	    }
       }
        if ((strncmp(buff, "exit", 4)) == 0) { 
            printf("Client ending....\n"); 
            break; 
        } 
    } 
} 

void send_file(FILE *fp, int sockfd)
{
	int n;
	char data[SIZE] = {0};

	while (fgets(data, SIZE, fp) != NULL) {
		if (send(sockfd, data, sizeof(data), 0) == -1) {
			perror("[-]Error in sending file.");
			exit(1);
		}
		bzero(data, SIZE);
	}
}

  
int main() 
{
    char *ip = "127.0.0.1";
    int e;    
    int sockfd, connfd; 
    struct sockaddr_in servaddr, cli; 
  
    FILE *fp;
    char *filename = "send.txt";

    // socket create and varification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
    bzero(&servaddr, sizeof(servaddr)); 
  
    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr(ip); 
    servaddr.sin_port = htons(PORT); 
 
    
    // connect the client socket to server socket 
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    } 
    // possible same code needs review
    if (e == -1) {
        perror("[1]Error in reading file.");
	exit(1);
    }

    else
        printf("connected to the server..\n"); 
  

    fp = fopen(filename, "r");
    // function for chat 
    func(sockfd,fp); 
  
    // close the socket 
    close(sockfd); 
} 

