#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#include<unistd.h>
// #include<fcntl.h>

int main(int argc, char ** argv)
{
    if(argc!=2)
    {
        printf("Usage: %s <port>",argv[0]);
        exit(0);
    }
    int port=atoi(argv[1]);
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[1024];
    socklen_t addr_size;

    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    memset(&server_addr,'\0',sizeof(server_addr));

    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(port);
    server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

    strcpy(buffer,"Hello Server!");
    sendto(sockfd,buffer,1024,0,(struct sockaddr*)&server_addr,sizeof(server_addr));
    printf("[+] Data Sent: %s\n",buffer);

    addr_size=sizeof(server_addr);
    recvfrom(sockfd,buffer,1024,0,(struct sockaddr*)&server_addr,&addr_size);
    printf("[+] Data Received: %s\n",buffer);

    return 0;
}

// nc -u -l -p <port>