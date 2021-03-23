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

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<k;j++)
        {
            printf("%d ",data[i][j]);
        }
        printf("<-Segment [%d] \n",(i+1));
    }
    printf("-----------------\n");
    for(int j=0;j<k;j++)
        printf("%d ",data[n][j]);
    printf("<-Sum1\n");
    carrynum=0;
    for(int i=k-1;i>=0;i--)
    {
        int sum=carrynum+carry[i]+data[n][i];
        data[n][i]=sum%2;
        carrynum=sum>0 ? sum>>1 : 0;
    }
    for(int i=0;i<k;i++)
        printf("%d ",carry[i]);
    printf("<-Carry\n");
    printf("-----------------\n");
    for(int i=0;i<k;i++)
    {   
        printf("%d ",data[n][i]);
        data[n][i]= data[n][i]==0 ? 1 : 0;
    }
    printf("<-Sum2\n");
    printf("-----------------\n");
    for(int i=0;i<k;i++)
    {
        printf("%d ",data[n][i]);
    }
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

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<k;j++)
        {
            printf("%d ",data[i][j]);
        }
        printf("<-Segment [%d] \n",(i+1));
    }
    for(int i=0;i<k;i++)
    {
        printf("%d ",data[n][i]);
    }
    printf("<-CHECKSUM (Receiver)\n");
    printf("-----------------\n");
    for(int j=0;j<k;j++)
        printf("%d ",chkBucket[j]);
    printf("<-Sum1\n");
    carrynum=0;
    for(int i=k-1;i>=0;i--)
    {
        int sum=carrynum+carry[i]+chkBucket[i];
        chkBucket[i]=sum%2;
        carrynum=sum>0 ? sum>>1 : 0;
    }
    for(int i=0;i<k;i++)
        printf("%d ",carry[i]);
    printf("<-Carry\n");
    printf("-----------------\n");
    for(int i=0;i<k;i++)
    {
        printf("%d ",chkBucket[i]);
        chkBucket[i]=chkBucket[i]==0 ? 1 : 0;
    }
    printf("<-Sum2\n");
    printf("-----------------\n");
    bool accept=true;
    for(int i=0;i<k;i++)
    {
        printf("%d ",chkBucket[i]);
        if(chkBucket[i]!=0)
            accept=false;
    }
    printf("<-CHECKSUM\n");
    printf("%s",(accept ? "Accepted!" : "Rejected!"));
    printf("\n");
    if(accept)
    {
        printf("Received Message is:\t");
        for(int i=0;i<n;i++)
        {
            int test[8];
            for(int j=15;j>=8;j--)
                test[15-j]=data[i][j];
            int b=binToDec(test,8);
            // printf("\n%d\n",b);
            printf("%c",(char)b);
            for(int j=7;j>=0;j--)
                test[7-j]=data[i][j];
            b=binToDec(test,8);
            printf("%c",(char)b);
        }
        printf("\n");
    }
}

int main()
{
    printf("Welcome to CHECKSUM Generation and Validation Program by cYpHeR under Dr. Salim\n");
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
        for(int j=15;j>=8;j--)
            data[i][j]=m1[y++];
        y=0;
        for(int j=7;j>=0;j--)
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
                    for(int j=15;j>=8;j--)
                        data[i][j]=m1[y++];
                    y=0;
                    for(int j=7;j>=0;j--)
                        data[i][j]=m2[y++];
                }
                break;
        case 'n':
            printf("Transmission successfull without error!\n");
            break;
    }
    checksumChk(data,n,k);
}