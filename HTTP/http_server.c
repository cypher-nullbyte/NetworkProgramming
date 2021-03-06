#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>
#include<unistd.h>
// #include<fcntl.h>

int main()
{
    //open a file to serve
    FILE *html_data;
    html_data= fopen("./index.html","r");
    
    char response_data[1024];
    fgets(response_data,1024,html_data);
    
    char http_header[2048]="HTTP/1.1 200 OK\r\n\n";
    strcat(http_header,response_data);
    
    //Create a socket
    int server_socket;
    server_socket=socket(AF_INET,SOCK_DGRAM,0);

    //DEFINE THE ADDRESS
    struct sockaddr_in server_address;
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(8001);
    server_address.sin_addr.s_addr=INADDR_ANY;

    bind(server_socket,(struct sockaddr *)&server_address,sizeof(server_address));
    int client_socket;
    while(1)
    {

        client_socket=accept(server_socket,NULL,NULL);
        socklen_t len=sizeof(client_socket);
        sendto(client_socket,http_header,sizeof(http_header),0,(struct sockaddr*)&client_socket,len);

        close(client_socket);
    }
    return 0;
}