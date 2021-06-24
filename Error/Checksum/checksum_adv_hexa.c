#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>

int* decToBin(int dec,int n)
{
    int * bin=(int *)calloc(n,sizeof(int));
    for(int i=n-1;i>=0;i--)
    {
        bin[i]=dec%2;
        dec/=2;
    }
    return bin;
}

char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}


char* binToHex(int bin[],int n)
{
    int hexConstant[] = {0, 1, 10, 11, 100, 101, 110, 111, 1000, 
                         1001, 1010, 1011, 1100, 1101, 1110, 1111};

    long long binary=0, tempBinary;
    for(int i=0;i<8;i++)
    {
        binary+=bin[i]*((int)pow(10,n-i-1));
    }
    char *hex=(char*)malloc(sizeof(char)*20);
    int index, i, digit;
    
    // printf("%lld",binary);
    
    /* Copy binary number to temp variable */
    tempBinary = binary;
    index = 0;
    
    /* Find hexadecimal of binary number */
    while(tempBinary!=0)
    {
        /* Group binary to last four digits */
        digit = tempBinary % 10000;

        /* Find hexadecimal equivalent of last four digit */
        for(i=0; i<16; i++)
        {
            if(hexConstant[i] == digit)
            {
                if(i<10)
                {
                    /* 0-9 integer constant */
                    hex[index] = (char)(i + 48);
                }
                else
                {
                    /* A-F character constant */
                    hex[index] = (char)((i-10) + 65);
                }

                index++;
                break;
            }
        }

        /* Remove the last 4 digits as it is processed */
        tempBinary /= 10000;
    }
    hex[index] = '\0';

    /* Reverse the hex digits */
    strrev(hex);

    return hex;
}

int binToDec(int bin[], int n)
{
    int dec=0;
    for(int i=n-1;i>=0;i--)
        dec+=bin[i]*((int)pow(2,n-i-1));
    return dec;
}

void checksumGen(int **data,int n,int k)
{
    int carrynum=0;
    for(int j=k-1;j>=0;j--)
    {
        int sum=0;
        for(int i=0;i<n;i++)
        {
            sum+=data[i][j];
        }
        sum+=carrynum;
        data[n][j]=sum%2;
        carrynum=sum>0 ? sum>>1 : 0;
    }
    int *carry=decToBin(carrynum,k);
    int temp1[8];
    int temp2[8];
    for(int i=0;i<n;i++)
    {     
        for(int j=0;j<8;j++)  temp1[j]=data[i][j];
        for(int j=8;j<16;j++)  temp2[j%8]=data[i][j];
        printf("%s ",binToHex(temp1,8));
        printf("%s ",binToHex(temp2,8));
        printf("<-Segment [%d] \n",(i+1));
    }
    printf("-----------------\n");
    for(int j=0;j<8;j++)  temp1[j]=data[n][j];
    for(int j=8;j<16;j++)  temp2[j%8]=data[n][j];
    printf("%s ",binToHex(temp1,8));
    printf("%s ",binToHex(temp2,8));
    printf("<-Sum1\n");
    carrynum=0;
    for(int i=k-1;i>=0;i--)
    {
        int sum=carrynum+carry[i]+data[n][i];
        data[n][i]=sum%2;
        carrynum=sum>0 ? sum>>1 : 0;
    }
    for(int j=0;j<8;j++)  temp1[j]=carry[j];
    for(int j=8;j<16;j++)  temp2[j%8]=carry[j];
    printf("%s ",binToHex(temp1,8));
    printf("%s ",binToHex(temp2,8));
    printf("<-Carry\n");
    printf("-----------------\n");
    for(int i=0;i<8;i++)
    {   
        temp1[i]=data[n][i];
        data[n][i]= data[n][i]==0 ? 1 : 0;
    }
    for(int i=8;i<16;i++)
    {   
        temp2[i%8]=data[n][i];
        data[n][i]= data[n][i]==0 ? 1 : 0;
    }
    printf("%s ",binToHex(temp1,8));
    printf("%s ",binToHex(temp2,8));
    printf("<-Sum2\n");
    printf("-----------------\n");
    for(int j=0;j<8;j++)  temp1[j]=data[n][j];
    for(int j=8;j<16;j++)  temp2[j%8]=data[n][j];
    printf("%s ",binToHex(temp1,8));
    printf("%s ",binToHex(temp2,8));
    printf("<-CHECKSUM\n");
}

void checksumChk(int **data,int n,int k)
{
    int *chkBucket=(int *)calloc(k,sizeof(int));
    int carrynum=0;
    for(int j=k-1;j>=0;j--)
    {
        int sum=0;
        for(int i=0;i<=n;i++)
        {
            sum+=data[i][j];
        }
        sum+=carrynum;
        chkBucket[j]=sum%2;
        carrynum=sum>0 ? sum>>1 : 0;
    }
    int *carry=decToBin(carrynum,k);
    int temp1[8];
    int temp2[8];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<8;j++)  temp1[j]=data[i][j];
        for(int j=8;j<16;j++)  temp2[j%8]=data[i][j];
        printf("%s ",binToHex(temp1,8));
        printf("%s ",binToHex(temp2,8));
        printf("<-Segment [%d] \n",(i+1));
    }
    for(int j=0;j<8;j++)  temp1[j]=data[n][j];
    for(int j=8;j<16;j++)  temp2[j%8]=data[n][j];
    printf("%s ",binToHex(temp1,8));
    printf("%s ",binToHex(temp2,8));
    printf("<-CHECKSUM (Receiver)\n");
    printf("-----------------\n");
    for(int j=0;j<8;j++)  temp1[j]=chkBucket[j];
    for(int j=8;j<16;j++)  temp2[j%8]=chkBucket[j];
    printf("%s ",binToHex(temp1,8));
    printf("%s ",binToHex(temp2,8));
    printf("<-Sum1\n");
    carrynum=0;
    for(int i=k-1;i>=0;i--)
    {
        int sum=carrynum+carry[i]+chkBucket[i];
        chkBucket[i]=sum%2;
        carrynum=sum>0 ? sum>>1 : 0;
    }
    for(int j=0;j<8;j++)  temp1[j]=carry[j];
    for(int j=8;j<16;j++)  temp2[j%8]=carry[j];
    printf("%s ",binToHex(temp1,8));
    printf("%s ",binToHex(temp2,8));
    printf("<-Carry\n");
    printf("-----------------\n");
    
    for(int i=0;i<8;i++)
    {   
        temp1[i]=chkBucket[i];
        chkBucket[i]=chkBucket[i]==0 ? 1 : 0;
    }
    for(int i=8;i<16;i++)
    {   
        temp2[i%8]=chkBucket[i];
        chkBucket[i]=chkBucket[i]==0 ? 1 : 0;
    }
    printf("%s ",binToHex(temp1,8));
    printf("%s ",binToHex(temp2,8));
    printf("<-Sum2\n");
    printf("-----------------\n");
    bool accept=true;
    for(int i=0;i<8;i++)
    {
        temp1[i]=chkBucket[i];
        if(chkBucket[i]!=0)
            accept=false;
    }
    for(int i=8;i<16;i++)
    {
        temp2[i%8]=chkBucket[i];
        printf("%d ",chkBucket[i]);
        if(chkBucket[i]!=0)
            accept=false;
    }
    printf("%s ",binToHex(temp1,8));
    printf("%s ",binToHex(temp2,8));
    printf("<-CHECKSUM\n");
    printf("%s",(accept ? "Accepted!" : "Rejected!"));
    printf("\n");
    if(accept)
    {
        printf("Received Message is:\t");
        for(int i=0;i<n;i++)
        {
            int test[8];
            for(int j=0;j<8;j++)
                test[j]=data[i][j];
            int b=binToDec(test,8);
            // printf("\n%d\n",b);
            printf("%c",(char)b);
            for(int j=8;j<16;j++)
                test[j%8]=data[i][j];
            b=binToDec(test,8);
            printf("%c",(char)b);
        }
        printf("\n");
    }
}

int main()
{
    printf("CHIRANJEET SINGH | 19BCI0016\n");
    printf("--------------------\n");
    int n,k;
    printf("Enter Message: ");
    char msg[50];
    scanf("%[^\n]s",msg);
    n=((int)strlen(msg))%2==0 ? ((int)strlen(msg))/2 : ((int)strlen(msg))/2+1;
    k=16;
    int len=(n+1)*sizeof(int *)+ (n+1)*(k)*sizeof(int);
    int **data=(int **)malloc(len);
    int * ptr=(int *)(data+n+1);
    for(int i=0;i<n+1;i++)
        data[i]=(ptr+k*i);
    int x=0;
    for(int i=0;i<n;i++)
    {
        int num=(int)msg[x++];
        int *m1= decToBin(num,8);
        num=(int)msg[x++];
        int *m2=decToBin(num,8);
        int y=0;
        for(int j=0;j<8;j++)
            data[i][j]=m1[y++];
        y=0;
        for(int j=8;j<16;j++)
            data[i][j]=m2[y++];
    }
    checksumGen(data,n,k);
    printf("\nNow sender is sending the segments with checksum ... \n\n");
    printf("------------------------------------------\n");
    printf("Hello Transmission channel do you want to alter message (y/n): ");
    char choice;scanf(" %c",&choice);
    switch(choice)
    {
        case 'y':
                printf("Enter Message: ");
                char msg[50];
                scanf(" %[^\n]s",msg);
                n=((int)strlen(msg))%2==0 ? ((int)strlen(msg))/2 : ((int)strlen(msg))/2+1;
                int x=0;
                for(int i=0;i<n;i++)
                {
                    int num=(int)msg[x++];
                    int *m1= decToBin(num,8);
                    num=(int)msg[x++];
                    int *m2=decToBin(num,8);
                    int y=0;
                    for(int j=0;j<8;j++)
                        data[i][j]=m1[y++];
                    y=0;
                    for(int j=8;j<16;j++)
                        data[i][j]=m2[y++];
                }
                break;
        case 'n':
            printf("Transmission successfull without error!\n");
            break;
    }
    checksumChk(data,n,k);
}