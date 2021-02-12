#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<sys/socket.h>
#include<sys/types.h>

#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
// #include<fcntl.h>


int main(int argc, char *argv[])
{
    char *address;
    address=argv[1];

    int client_socket;
    client_socket=socket(AF_INET,SOCK_STREAM,0);

    //CONNECT TO ADDRESS
    struct sockaddr_in remote_address;
    remote_address.sin_family=AF_INET;
    remote_address.sin_port=htons(80);
    remote_address.sin_addr.s_addr=INADDR_ANY;
    inet_aton(address,&remote_address.sin_addr);
    connect(client_socket,(struct sockaddr*) &remote_address, sizeof(remote_address));
    
    char request[]="GET / HTPP2.0/\r\n\n";
    char response[4096];
    send(client_socket,request,sizeof(request),0);

    recv(client_socket,&response,sizeof(response),0);

    printf("resonse from the server: %s\n",response);
    close(client_socket);
}