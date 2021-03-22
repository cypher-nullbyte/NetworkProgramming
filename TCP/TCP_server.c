#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
//#include<fcntl.h>



int main(int argc, char* argv[])
{
    if(argc!=2)
    {
        printf("Usage: %s <port>",argv[0]);
        exit(0);
    }
    int port=atoi(argv[1]);
    char server_message[256]="You have reached the server!";

    //CREATE THE SERVER SOCKET
    int server_socket;
    server_socket=socket(AF_INET,SOCK_STREAM,0);
    printf("%d\n",server_socket);
    
    //define the server address
    struct sockaddr_in server_address;
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(port);
    // server_address.sin_addr.s_addr=INADDR_ANY;
    server_address.sin_addr.s_addr=inet_addr("127.0.0.1");

    //bind the socket to our specified IP and port
    bind(server_socket,(struct sockaddr*) &server_address,sizeof(server_address));
    listen(server_socket,5); 

    int client_socket;
    // client_socket=accept(server_socket,NULL,NULL);
    struct sockaddr_in client_address;
    socklen_t cliLen=sizeof(client_address);
    client_socket=accept(server_socket,(struct sockaddr*)&client_address,&cliLen);
    printf("%d\n",client_socket);
    //send the message
    send(client_socket,server_message,sizeof(server_message),0);

    //close the connection
    close(server_socket);
    
    return 0;
}