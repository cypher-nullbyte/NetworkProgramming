#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>



char * stringToBinary(char *s)
{
    char *b=(char*)calloc(strlen(s)*8+1,sizeof(char));
    for(int i=0;i<strlen(s);i++)
    {
        char byte_bucket[9]={"0"};
        byte_bucket[8]='\0';
        int ch=(int)s[i];
        int j=7;
        while(ch>1)
        {
            byte_bucket[j--]=(ch%2 +'0');
            ch/=2;
        }
        byte_bucket[j]='1';
        strcat(b,byte_bucket);
    }
    return b;
}

char * binaryToString(char *b)
{
    char *s=(char *)calloc(strlen(b)/8+1,sizeof(char));
    int ptr=0;
    for(int i=0;i<strlen(b);i+=8)
    {
        int asci=0;
        for(int j=i;j<i+8;j++)
        {
            asci+=((int)(b[j]-'0'))*((int)pow(2,7-(j-i)));
        }
        s[ptr++]=(char)asci;
    }
    return s;
}



int main()
{
    printf("-----WELCOME TO OSI MODEL SIMULATION BY CYPHER UNDER DR. SALEEM DURAI M.A.------\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("HELLO USER I'M APPLICATION LAYER  PLEASE ENTER DATA TO SEND TO Dr. SALEEM: ");
    char data1[10];
    scanf("%s",data1);

    printf("\n--------------------------------------------------------------------------------\n");

    printf("Application Layer on its work. We're adding header H1");
    char data2[14]="[xx]";
    strcat(data2,data1);
    printf("I will ship this data to Presentation layer: %s\n",data2);

    printf("\n--------------------------------------------------------------------------------\n");

    printf("I'm presentation Layer, I will encrypt your Data using and  pass to session layer.\n");
    char data3[18]="[xx]";
    strcat(data3,data2);
    printf("I'll ship this data to Session Layer: %s\n",data3);

    printf("\n--------------------------------------------------------------------------------\n");

    printf("I'm Session Layer, I will maintain Session for you and send data to Transport layer.\n");
    char data4[22]="[xx]";
    strcat(data4,data3);
    printf("I'll ship this data to Presentation Layer: %s\n",data4);

    printf("\n--------------------------------------------------------------------------------\n");

    printf("I'm Transport Layer. I'll attach process details to be handled at other end. Then I'll send to Network Layer\n");
    char data5[26]="[xx]";
    strcat(data5,data4);
    printf("I'll ship this data to Network Layer: %s\n",data5);

    printf("\n--------------------------------------------------------------------------------\n");

    printf("I'm Network Layer. I'll attach Virtual Address details to be handled at other end. Then I'll send Packet to DataLink Layer\n");
    char data6[30]="[xx]";
    strcat(data6,data5);
    printf("I'll ship this Packet to DataLink Layer: %s\n",data6);

    printf("\n--------------------------------------------------------------------------------\n");

    printf("I'm DataLink Layer. I'll add physical address and checksum trailer. Then I'll send Frame to Phyical Layer\n");
    char data7[38]="[xx]";
    char trailer[]="[xx]";
    strcat(data7,data6);
    strcat(data7,trailer);
    printf("I'll ship this Frame to Physical Layer: %s\n",data7);

    printf("\n--------------------------------------------------------------------------------\n");

    printf("I'm Physical Layer. I will send things in bits.\n");
    char data8[42]="[xx]";
    strcat(data8,data7);
    char *bits=stringToBinary(data8);

    printf("I'll ship these bits to very next Physical layer at other end: %s\n",bits);

    printf("\n--------------------------------------------------------------------------------\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("I'm the physical layer at Dr. Salim's Side. I'll convert data bits into Frames for data link .\n");
    char *received=binaryToString(bits);
    printf("After Converting from bits to string format, I have: %s\n",received);
    received+=4;
    printf("After removing my header, I've this DataFrame: %s\n",received);

    printf("\n--------------------------------------------------------------------------------\n");

    printf("I'm the DataLink layer at Dr. Salim's Side. I'll convert data Frames into packets for Network Layer.\n");
    strncpy(received,received,strlen(received)-4);
    received[strlen(received)-4]='\0';
    received+=4;
    printf("After removing Header and Trailer I've this DataPacket: %s\n",received);

    printf("\n--------------------------------------------------------------------------------\n");

    printf("I'm the Network layer, I'll remove my header from  packet and send to Transport Layer\n");
    received+=4;
    printf("After removing my header, I've this data: %s\n",received);

    printf("\n--------------------------------------------------------------------------------\n");

    printf("I'm the Transport layer, I'll remove my  header  and send to Sesseion Layer\n");
    received+=4;
    printf("After removing my header, I've this data: %s\n",received);

    printf("\n--------------------------------------------------------------------------------\n");

    printf("I'm the Session layer, I'll remove my header and send data to Presentation Layer.\n");
    received+=4;
    printf("After removing my header, I've this data: %s\n",received);

    printf("\n--------------------------------------------------------------------------------\n");

    printf("I'm the Presentation layer, I'll remove my header and send data to Application Layer.\n");
    received+=4;
    printf("After removing my header, I've this data: %s\n",received);

    printf("\n--------------------------------------------------------------------------------\n");

    printf("I'm the Application layer, I'll remove my header so you can read message.\n");
    received+=4;
    printf("After removing my header, I've this message for Dr. Salim: %s\n",received);
    return 0;
}

