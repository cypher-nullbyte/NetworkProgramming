#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h> //gethostbyname

#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#include<unistd.h>
// #include<fcntl.h>

void error (const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char ** argv)
{
    int sockfd, portno,n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    
    
    char buffer[256];
    if(argc!=3)
    {
        fprintf(stderr,"Usage: %s <hostname> <port>",argv[0]);
        exit(0);
    }
    portno=atoi(argv[2]);
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0)
        error("ERROR opening socket...");
    server=gethostbyname(argv[1]);
    if(server==NULL)
    {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char*)&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(portno);
    if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
        error("ERROR connecting...");
    while(1)
    {
        bzero(buffer,256);
        fgets(buffer,255,stdin);
        n=write(sockfd,buffer,strlen(buffer));
        if(n<0)
            error("ERROR writing to socket");
        bzero(buffer,256);
        n=read(sockfd,buffer,255);
        if(n<0)
            error("ERROR reading from socket...");
        printf("Server: %s\n",buffer);
        int i=strncmp(".exit",buffer,5);
        if(i==0)
            break;
    }
    close(sockfd);
    return 0;
}