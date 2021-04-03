#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>
#include<arpa/inet.h>

#include<unistd.h>
#include <time.h>

typedef struct{
    char data[1024];
}Packet;

typedef struct{
    int frame_kind;
    int sq_no;
    int ack;
    Packet packet;
}Frame;


void main(int argc, char **argv)
{
    if(argc!=2)
    {
        printf("Usage: %s <port>\n",argv[0]);
        exit(0);
    }
    int port=atoi(argv[1]);
    int sockfd;
    struct sockaddr_in serverAddr, newAddr;
    char buffer[1024];
    socklen_t addr_size;

    int frame_id=0;
    Frame frame_send;
    Frame frame_recv;
    int ack_recv=1;

    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    memset(&serverAddr,'\0',sizeof(serverAddr));
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(port);
    serverAddr.sin_addr.s_addr=inet_addr("127.0.0.1");

    while(1){

        if(ack_recv==1){
            frame_send.sq_no=frame_id;
            frame_send.frame_kind=1;
            frame_send.ack=0;
            printf("Enter Data: ");
            scanf("%s",buffer);
            strcpy(frame_send.packet.data,buffer);
            again:
            sendto(sockfd,&frame_send,sizeof(Frame),0,(struct sockaddr*)&serverAddr,sizeof(serverAddr));
            printf("[+]Frame {%d | %d} sent\n",frame_send.sq_no,(frame_send.sq_no%2));
        }
        int addr_size=sizeof(serverAddr);
        int f_recv_size=-1;
        int seconds=2;
        clock_t endwait;
        endwait = clock () + seconds * CLOCKS_PER_SEC ;
        while (clock() < endwait) {
            f_recv_size=recvfrom(sockfd,&frame_recv,sizeof(Frame),MSG_DONTWAIT,(struct sockaddr*)&serverAddr,&addr_size);
            if(f_recv_size!=-1) break;
        }
        // printf("%d\n",f_recv_size);
        if(f_recv_size>0 && frame_recv.sq_no==0 && frame_recv.ack==frame_id+1){
            printf("[+] ACK {%d | %d} Received\n",frame_recv.ack,(frame_recv.ack%2));
            ack_recv=1;
            frame_id++;
        }else{
            printf("[-]ACK Not Received or corrupted.\n");
            printf("[+]Sending Again!\n");
            ack_recv=1;
            goto again;
        }
        
    }
    close(sockfd);

}


