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
        fprintf(stderr,"Usage: %s <hostnam> <port>",argv[0]);
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
    
    int num1,num2,choice,ans;
    S: 
    bzero(buffer,255);
    n=read(sockfd,buffer,255);
    if(n<0)
        error("ERROR reading from socket...");
    printf("Server- %s\n",buffer);
    scanf("%d",&num1);
    write(sockfd,&num1,sizeof(int));

    bzero(buffer,255);
    n=read(sockfd,buffer,255);
    if(n<0)
        error("ERROR reading from socket...");
    printf("Server- %s\n",buffer);
    scanf("%d",&num2);
    write(sockfd,&num2,sizeof(int));

    bzero(buffer,255);
    n=read(sockfd,buffer,255);
    if(n<0)
        error("ERROR reading from socket...");
    printf("Server- %s\n",buffer);
    scanf("%d",&choice);
    write(sockfd,&choice,sizeof(int));
    
    if(choice==0)
        goto Q;
 
    
    n=read(sockfd,&ans,sizeof(int));
    if(n<0)
        error("ERROR reading from  socket...");
    printf("Server-The answer is: %d\n",ans);
    goto S;

    Q:
    printf("You have select to exit.\n Exit successfull!");
    close(sockfd);
    return 0;
}