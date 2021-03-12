#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct{
    char positives[3];
    int MPN;
    int CL[2];
}BacteriaSample;


void dataFiller(BacteriaSample *s,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<3;j++)
            scanf(" %c",&(*s).positives[j]);
        scanf("%d",&(*s).MPN);
        for(int j=0;j<2;j++)
            scanf("%d",&(*s).CL[j]);
        s++;
    }
    

}
void infoDisplayer(BacteriaSample *s,char* positives,int n)
{
    
    for(int i=0;i<n;i++)
    {
        if(s->positives[0]==positives[0] && s->positives[1]==positives[1] && s->positives[2]==positives[2]) 
        {
            printf("Match Found!\n");
            printf("MNPN: %d\n",(*s).MPN);
            printf("Lower & Upper Confidence Limits: %d\t%d",s->CL[0],s->CL[1]);
            return;
        }
        printf("Match not Found!");
        s++;
    }
}
int main()
{
    int n;
    printf("Enter How many Samples You need to work with: ");
    scanf("%d",&n);
    BacteriaSample *s=(BacteriaSample *)calloc(n,sizeof(BacteriaSample));
    dataFiller(s,n);
    printf("\n--------------------------------------------\n");
    char positivesToFind[3];
    for(int i=0;i<3;i++)
        scanf(" %c",&positivesToFind[i]);
    infoDisplayer(s,positivesToFind,n);
    return 0;
}