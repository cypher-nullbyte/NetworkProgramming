#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<strings.h> //bzero

#include<netinet/in.h>
#include<arpa/inet.h>

#include<sys/socket.h>
#include<sys/types.h>

#include<unistd.h>
// #include<fcntl.h>


void communicate(int);

int main(int argc, char** argv)
{

     if(argc!=2)
    {
        fprintf(stderr,"Usage: %s <port>\n",argv[0]);
        exit(1);
    }
    int PORT=atoi(argv[1]);
    int sockfd;
    struct sockaddr_in servaddr;

    //CREATE SOCKET
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd==-1)
    {
        printf("Socket Creation failed...\nClosing Server...\n");
        exit(1);
    }
    else printf("Socket Creation Successfull...\n");
    bzero(&servaddr,sizeof(servaddr));
    
    //Internet Protocol
    servaddr.sin_family=AF_INET;
    //Address Port
    servaddr.sin_port=htons(PORT);
    //Internet Address
    servaddr.sin_addr.s_addr=inet_addr("127.0.0.1"); 

    //BINDING SOCKET
    // --- status=bind(sockid,&addrport,size)
    if(bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))!=0)
    {
        printf("Socket Binding failed...\nClosing Server...\n");
        exit(1);
    }
    else printf("Socket Binding Successfull...\n");

    //COMMUNICATION
    communicate(sockfd);

    //CLOSE SOCKET
    close(sockfd);

    return 0;
}


void communicate(int sockfd)
{
    struct sockaddr_in cli;
    socklen_t len=sizeof(cli);
    char buffer[256];
    int n;
    while(1)
    {
        int c;
        n=0;
        bzero(buffer,256);
        recvfrom(sockfd,buffer,256,0,(struct sockaddr*)&cli,&len);

        printf("Client: %s\n",buffer);

        bzero(buffer,256);
        fseek(stdin,0,SEEK_END);

        printf("Enter Message: ");
        while((c=buffer[n++]=getchar())!='\n' && c!=EOF );
        sendto(sockfd,buffer,256,0,(struct sockaddr*)&cli,len);

        //Check for .exit
        if(strncmp(".exit",buffer,5)==0)
        {
            printf("Client Sent Request to exit...\nServer Exiting....");

            break;
        }
    }
}