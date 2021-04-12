#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#include<unistd.h>
// #include<fcntl.h>

void error(const char * msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char * argv[])
{
    if(argc!=2)
    {
        fprintf(stderr,"Usage: %s <port>\n",argv[0]);
        exit(1);
    }

    int sockfd,newsockfd,portno,n;
    char buffer[255];

    struct sockaddr_in serv_addr,cli_addr;
    socklen_t clilen;

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0)
    {
        error("Error opening socket...");
    }
    bzero((char *)&serv_addr,sizeof(serv_addr));
    portno=atoi(argv[1]);

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(portno);
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1"); //or INADDR_ANY

    if(bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
    {
        error("Binding failed...");
    }
    
    listen(sockfd,5);
    clilen=sizeof(cli_addr);
    newsockfd=accept(sockfd,(struct sockaddr*) &cli_addr,&clilen);
    if(newsockfd<0)
        error("Error on Accept!");

    while(1)
    {
        bzero(buffer,255);
        n=read(newsockfd,buffer,255);
        if(n<0)
            error("Error on reading!");
        printf("Client: %s\n",buffer);
        bzero(buffer,255);
        fgets(buffer,255,stdin);
        n=write(newsockfd,buffer,strlen(buffer));
        if(n<0)
            error("Error on writing!");
        int i=strncmp(".exit",buffer,5);
        if(i==0)
            break;
    }
    close(newsockfd);
    close(sockfd);
    return 0;
}