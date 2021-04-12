#include<stdio.h>
#include<netdb.h> //gethostname
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>


#include<unistd.h>
#include<fcntl.h>


void communicate(int);

int main(int argc, char** argv)
{

     if(argc!=3)
    {
        fprintf(stderr,"Usage: %s <ip> <port>\n",argv[0]);
        exit(1);
    }
    int PORT=atoi(argv[2]);
    struct hostent *server;
    int sockfd,connfd,len;
    struct sockaddr_in servaddr;

    // server=gethostbyname(argv[1]);

    //CREATE SOCKET
    sockfd=socket(AF_INET,SOCK_STREAM,0);
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
   //CONNECT
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) 
    { 
        printf("Connection with the server failed...\nClosing Client...\n"); 
        exit(0); 
    } 
    else
	printf("Connected to the server..\n"); 

    //COMMUNICATION
    communicate(sockfd);

    //CLOSE SOCKET

    close(sockfd);

    return 0;
}


void communicate(int connfd)
{
    char buffer[256];
    int n;
    while(1)
    {
        n=0;
        bzero(buffer,256);
        fseek(stdin,0,SEEK_END);
        int c;
        
        printf("Enter Message: ");
        while((c=buffer[n++]=getchar())!='\n' && c!= EOF);
        write(connfd,buffer,sizeof(buffer));
        
        bzero(buffer,256);

        read(connfd,buffer,sizeof(buffer));

        printf("Server: %s\n",buffer);

        
        //Check for .exit
        if(strncmp(".exit",buffer,5)==0)
        {
            printf("Server Sent Request to exit...\nClient Exiting....");
            break;
        }

    }
    close(connfd);

}
