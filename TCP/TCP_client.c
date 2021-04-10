#include<stdio.h>
#include<stdlib.h>

#include<sys/socket.h>
#include<sys/types.h>

#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
// #include<fcntl.h>

int main(int argc, char **argv)
{
    if(argc!=2)
    {
        printf("Usage: %s <port>",argv[0]);
        exit(0);
    }
    int port=atoi(argv[1]);

    //create a socket
    int network_socket;
    network_socket=socket(AF_INET,SOCK_STREAM,0);
    printf("%d\n",network_socket);
    //specify an address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(port);
    // server_address.sin_addr.s_addr=INADDR_ANY;
    server_address.sin_addr.s_addr=inet_addr("127.0.0.1");
    int connection_status=connect(network_socket,(struct sockaddr*)&server_address,sizeof(server_address));

    //check for error with the connection
    if(connection_status==-1)
    {
        printf("There was an error while making connection to the remote socket\n\n");
        exit(0);
    }

    //receive data from the server
    char server_response[256];
    recv(network_socket,server_response,sizeof(server_response),0);

    //print the server's response
    printf("The server sent the data: %s\n",server_response);

    //and then close the socket
    close(network_socket);
    return 0;
}

// UDP +