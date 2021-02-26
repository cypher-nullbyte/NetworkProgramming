#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

<<<<<<< HEAD
#include<netinet/in.h>
#include<unistd.h>
// #include<fcntl.h>


int main()
{
    char server_message[256]="You have reached the server!";
    //create the server socket;
    int server_socket;
    server_socket=socket(AF_INET,SOCK_STREAM,0);

    //define the server address;
    struct sockaddr_in server_address;
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(9002);
    server_address.sin_addr.s_addr=INADDR_ANY;

    //bind the socket to our speified IP and port
    bind(server_socket,(struct sockaddr*) &server_address,sizeof(server_address));
    listen(server_socket,5);
    
=======
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
    
    //define the server address
    struct sockaddr_in server_address;
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(port);
    // server_address.sin_addr.s_addr=INADDR_ANY;
    server_address.sin_addr.s_addr=inet_addr("127.0.0.1");

    //bind the socket to our specified IP and port
    bind(server_socket,(struct sockaddr*) &server_address,sizeof(server_address));
    listen(server_socket,5); 
>>>>>>> c370573... Till checksum

    int client_socket;
    client_socket=accept(server_socket,NULL,NULL);

    //send the message
    send(client_socket,server_message,sizeof(server_message),0);

    //close the connection
<<<<<<< HEAD

    close(server_socket);
=======
    close(server_socket);
    
>>>>>>> c370573... Till checksum
    return 0;
}