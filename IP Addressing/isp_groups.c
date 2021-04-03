#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct
{
    int first,second,third,fourth;
    int mask;
}Address;

typedef struct{
    int no_cust;
    int add_per_cust;
    Address *start,*end;
}Group;

Address* readAddress()
{
    Address *add=(Address*)malloc((sizeof(Address)));
    scanf("%d%d%d%d%d",&(add->first),&(add->second),&(add->third),&(add->fourth),&(add->mask));
    return add;
}

void printAddress(Address *add)
{
    printf("%d.%d.%d.%d/%d\n",add->first,add->second,add->third,add->fourth,add->mask);
}

Address * createAddress()
{
    Address *add=(Address*)malloc(sizeof(Address));
    return add;
}

int main()
{
    printf("Welcome to ISP Addressing Solver by cYpHeR under Dr. Saleem!\n\n");
    Address *ISP;
    printf("Enter Network IP and Mask of ISP: ");
    ISP=readAddress();
    printf("The ISP has Network has [%d] addresses starting with address :",(int)pow(2,32-ISP->mask));
    printAddress(ISP);
    int n;
    printf("Enter the number of groups you want to create: ");
    scanf("%d",&n);
    Group *grps=(Group*)calloc(n,sizeof(Group));
    for(int i=0;i<n;i++)
    {
        printf("Enter the number of customers and addresses_addresses per customer for Group[%d] : ",(i+1));
        scanf("%d%d",grps[i].no_cust,grps[i].add_per_cust);
    }
    Address *temp=ISP;
    for(int i=0;i<n;i++)
    {
        int x=0;
        while((int)pow(2,x)<grps[i].add_per_cust) x++;
        grps[i].start=createAddress();
        grps[i].end=createAddress();
        grps[i].start->mask=32-x;
    }
    
    return 0;
}
//2001:0db8:85a3:0:0:8a2e:0370:7334