#include<iostream>
#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
#include<strings.h>
#include<unistd.h>
#define cls() printf("33[H33[J (cleaned buffer)")
//structure definition for designing the frame.

struct window
{
 int frame[40];
};

//structure definition for accepting the acknowledgement.
struct ack
{
 int acknowledge[40];
};

int main()
{
 int serversocket;
 sockaddr_in serveraddr,clientaddr;
 socklen_t len;
 int windowsize,totalpackets,totalframes,framessend=0,i=0,j=0,k,l,m,n,repacket[40];
 ack acknowledgement;
 window f1;
 char req[50];
 serversocket=socket(AF_INET,SOCK_DGRAM,0);
 bzero((char*)&serveraddr,sizeof(serveraddr));
 serveraddr.sin_family=AF_INET;
 serveraddr.sin_port=htons(5018);
 serveraddr.sin_addr.s_addr=INADDR_ANY;
 
 bind(serversocket,(sockaddr*)&serveraddr,sizeof(serveraddr));
 bzero((char*)&clientaddr,sizeof(clientaddr));
 len=sizeof(clientaddr);
//connection establishment.
 printf("\nWaiting for client connection.\n");
 recvfrom(serversocket,req,sizeof(req),0,(sockaddr*)&clientaddr,&len);
 printf("\nThe client connection obtained.\t%s\n",req);
 
//sending request for windowsize.
 printf("\nSending request for window size.\n");
 sendto(serversocket,"REQUEST FOR WINDOWSIZE.",sizeof("REQUEST FOR WINDOWSIZE."),0,(sockaddr*)&clientaddr,sizeof(clientaddr));
//obtaining windowsize.
 printf("\nWaiting for the windowsize.\n");
 recvfrom(serversocket,(char*)&windowsize,sizeof(windowsize),0,(sockaddr*)&clientaddr,&len);
 cls();
 printf("\nThe windowsize obtained as:\t%d\n",windowsize);
 printf("\nObtaining frames from network layer.\n");
 printf("\nTotal frames obtained:\t%d\n",(totalpackets=windowsize*5));
 printf("\nTotal windows to be transmitted:\t%d\n",(totalframes=5));
//sending details to client.
sendto(serversocket,(char*)&totalpackets,sizeof(totalpackets),0,(sockaddr*)&clientaddr,sizeof(clientaddr));
recvfrom(serversocket,req,sizeof(req),0,(sockaddr*)&clientaddr,&len);
printf("\nSending total number of frames.\n");
sendto(serversocket,(char*)&totalframes,sizeof(totalframes),0,(sockaddr*)&clientaddr,sizeof(clientaddr));
recvfrom(serversocket,req,sizeof(req),0,(sockaddr*)&clientaddr,&len);
printf("\nPRESS ENTER TO START THE PROCESS.\n");
fgets(req,2,stdin);
cls();
 j=0;
 l=0; //starting the process of sending
 while( l<totalpackets)
 {
//initialising the transmit buffer.
  bzero((char*)&f1,sizeof(f1));
  printf("\nInitialising the transmit buffer.\n");
  printf("\nThe window to be send is %d with frames:\t",framessend);
  //Builting the window.
  for(m=0;m<j;m++)
  {
  //including the frames for which negative acknowledgement was received.
   printf("%d  ",repacket[m]%(windowsize*2));
   f1.frame[m]=repacket[m];
  }
  while(j<windowsize && i<totalpackets)
  {
   printf("%d  ",i%(windowsize*2));
   f1.frame[j]=i;
   i++;
   j++;
  }
  printf("\nSending window %d\n",framessend);
  //sending the window.
  sendto(serversocket,(char*)&f1,sizeof(f1),0,(sockaddr*)&clientaddr,sizeof(clientaddr));
   //Waiting for the acknowledgement.
  printf("\nWaiting for the acknowledgement.\n");
  recvfrom(serversocket,(char*)&acknowledgement,sizeof(acknowledgement),0,(sockaddr*)&clientaddr,&len);
  cls();
 //Checking acknowledgement of each frame.
  j=0;
  k=0;
  m=0;
  n=l;
  while(m<windowsize && n<totalpackets)
  {
   if(acknowledgement.acknowledge[m]==-1)
   {
    printf("\nNegative acknowledgement received for Frame: %d\n",(f1.frame[m]%(windowsize*2)));
    k=1;
    repacket[j]=f1.frame[m];
    j++;
   }
   else
   {
    l++;
   }
   m++;
   n++;
  }
  if(k==0)
  {
    printf("\nPositive acknowledgement received for all frames within the window: %d\n",framessend);
  }
 
  framessend++;
  printf("\nPRESS ENTER TO PROCEED……\n");
  fgets(req,2,stdin);
  cls();
 }
 
 printf("\nAll frames send successfully.\n\nClosing connection with the client.\n");
 close(serversocket);
}