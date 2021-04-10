#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>

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

Address* readAndCreateAddress()
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
void copyIP(Address* newIP,Address *IP)
{
    newIP->first=IP->first;
    newIP->second=IP->second;
    newIP->third=IP->third;
    newIP->fourth=IP->fourth;
    newIP->mask=IP->mask;   
}

void incrementIP(Address *ip,int total)
{
    int counter=0;
    while(counter<total)
    {
        if(ip->fourth<255)
        {
            int x=255-ip->fourth;
            int increment=total-counter>x ? x: total-counter ;
            counter+=increment;
            ip->fourth+=increment;
        }
        else if(ip->third<255)
        {
            int x=255-ip->third;
            int increment=1 ;
            counter+=increment;
            ip->third+=increment;
            ip->fourth=0;
        }
        else if(ip->second<255)
        {
            int x=255-ip->second;
            int increment=1 ;
            counter+=increment;
            ip->second+=increment;
            ip->fourth=0;
            ip->third=0;
        }
        else if(ip->first<255)
        {
            int x=255-ip->first;
            int increment=1 ;
            counter+=increment;
            ip->first+=increment;
            ip->fourth=0;
            ip->third=0;
            ip->second=0;
        }
        printf("%d\t",counter);
    }
    printf("\n\n");
    printAddress(ip);
}

void distributeIP(Address *prev_hook,Address * START,Address *END, unsigned long total, unsigned long* LIMIT)
{
    if(total>*LIMIT)
    {
        printf("OVERLIMIT!!!!!!\n");
        exit(0);
    }
    copyIP(START,prev_hook);
    copyIP(END,START);
    *LIMIT-=total;
    incrementIP(END,total-1);
    copyIP(prev_hook,END);
    incrementIP(prev_hook,1);
}


int main()
{
    printf("Welcome to ISP Addressing Solver by cYpHeR under Dr. Saleem!\n\n");
    printf("Do a favour :) Please enter groups' details in descending order of IP req. per customer !!!\n\n");
    Address *ISP;
    printf("Enter Network IP and Mask of ISP: ");
    ISP=readAndCreateAddress();
    unsigned long *LIMIT=(unsigned long*)malloc(sizeof(unsigned long));
    *LIMIT=(unsigned long)pow(2,32-ISP->mask);
    printf("The ISP has Network has [%lu] addresses starting with address :",*LIMIT);
    printAddress(ISP);
    int n;
    printf("Enter the number of groups you want to create: ");
    scanf("%d",&n);

    Group **grps=(Group**)calloc(n,sizeof(Group*));

    for(int i=0;i<n;i++)
    {
        grps[i]=(Group*)malloc(sizeof(Group));
        printf("Enter the number of customers and addresses_addresses per customer for Group[%d] : ",(i+1));
        scanf("%d%d",&grps[i]->no_cust,&grps[i]->add_per_cust);
    }

    Address *prev_add=createAddress();
    copyIP(prev_add,ISP);
    for(int i=0;i<n;i++)
    {
        int x=0;
        while((int)pow(2,x)<grps[i]->add_per_cust) x++;
        printf("%d\n",x);
        grps[i]->start=createAddress();
        grps[i]->end=createAddress();
        grps[i]->start->mask=32-x;
        grps[i]->end->mask=32-x;
        prev_add->mask=32-x;
        distributeIP(prev_add,grps[i]->start,grps[i]->end,(unsigned long )grps[i]->no_cust*grps[i]->add_per_cust,LIMIT);
    }

    printf("END\n");
    return 0;
}