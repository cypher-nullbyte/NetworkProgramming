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


void communicate(int, struct sockaddr_in);

int main(int argc, char** argv)
{

if(argc!=3)
    {
        printf("Usage: %s <ip> <port>\n",argv[0]);
        exit(1);
    }
    int PORT=atoi(argv[2]);
    // struct hostent *server;
    int sockfd;
    struct sockaddr_in servaddr;

    // server=gethostbyname(argv[1]);

    //CREATE SOCKET
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd==-1)
    {
        printf("Socket Creation failed...\nClosing Client...\n");
        exit(1);
    }
    else printf("Socket Creation Successfull...\n");

    // server=gethostbyname(argv[1]);
    // if(server==NULL)
    // {
    //     fprintf(stderr,"ERROR, no such host\n");
    //     exit(0);
    // }

    bzero(&servaddr, sizeof(servaddr)); 
    
    //Internet Protocol
    servaddr.sin_family=AF_INET;
    //Address Port
    servaddr.sin_port=htons(PORT);
    //Internet Address
    servaddr.sin_addr.s_addr=inet_addr(argv[1]); 


    //COMMUNICATION
    communicate(sockfd,servaddr);

    //CLOSE SOCKET
    close(sockfd);

    return 0;
}


void communicate(int sockfd, struct sockaddr_in servaddr)
{
   
    socklen_t len=sizeof(servaddr);
    char buffer[256];
    int n;
    while(1)
    {
        int c;
        n=0;
        bzero(buffer,256);

        printf("Enter Message: ");
        while((c=buffer[n++]=getchar())!='\n' && c!=EOF );
        sendto(sockfd,buffer,256,0,(struct sockaddr*)&servaddr,len);

        bzero(buffer,256);

        recvfrom(sockfd,buffer,256,0,(struct sockaddr*)&servaddr,&len);

        printf("Server: %s\n",buffer);

        fseek(stdin,0,SEEK_END);

        //Check for .exit
        if(strncmp(".exit",buffer,5)==0)
        {
            printf("Server Sent Request to exit...\nClient Exiting....");
            break;
        }
    }
}