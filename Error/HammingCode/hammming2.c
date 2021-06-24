#include<stdio.h>
#include<math.h>   //pow
#include<stdlib.h> // calloc


int main()
{
    printf("Welcome to Hamming Code Generation, Detection and Correction Program by cYpHeR under Dr. Salim\n");
    printf("NOTE:- BIT INDEXING STARTS FROM [RIGHT TO LEFT], JUST LIKE IN TEXTBOOKS!\n\n");
    int m_size,rbit=0,msg[50],data[60],i,j,k;
    printf("Enter message size: ");
    scanf("%d",&m_size);

    //calculate no of rbits 2^rbit >= m_size + rbit +1
    while(1)
    {
        if((m_size+rbit+1)<=(int)pow(2,rbit))
            break;
        rbit++;
    }
    printf("RBit Size is: %d\n",rbit);
    printf("Enter message bits (space separted): ");
    for(i=m_size;i>=1;i--)
    {
        scanf("%d",&msg[i]);
    }
    k=0; // for 2^k
    j=1; // for positioning msg
    for(i=1;i<=(m_size+rbit);i++)
    {
        if(i==(int)pow(2,k))
        {
            data[i]=8;
            k++; 
        }
        else
        {
            data[i]=msg[j];
            j++;
        }
    }
    for(int i=(m_size+rbit);i>=1;i--)
    {
        printf("%d ",data[i]);
    }
    printf("\n");
    for(i=1;i<=(m_size+rbit);i++)
    {   
        if(data[i]==8)
        {
            data[i]=0;
            int count=0;
            for(j=i;j<=(m_size+rbit);j++)
            {
                for(k=0;k<i;k++)
                {
                    if(data[j]==1)
                    {
                        count++;
                    }
                    j++;
                }
                j=j+i-1;
            }
            if(count%2==0)
            {
                data[i]=0;
            }
            else
            {
                data[i]=1;
            }
        }
    }

    printf("This is the generated codeword: ");
    for(i=(m_size+rbit);i>=1;i--)
        printf("%d ",data[i]);
    printf("\n----------------------------------\n");
    printf("Enter received codeword: ");
    for(i=(m_size+rbit);i>=1;i--)
        scanf("%d",&data[i]);

    int c=0;
    // C1 C2 C3
    // D1 D2 D3
    // 0  1  0 ->2

    int *parities=(int *)calloc(rbit,sizeof(int));
    for(i=1;i<=(m_size+rbit);i++)
    {   
        if(i==(int)pow(2,c))
        {
            int count=0;
            for(j=i;j<=(m_size+rbit);j++)
            {
                for(k=0;k<i;k++)
                {
                    if(data[j]==1)
                    {
                        count++;
                    }
                    j++;
                }
                j=j+i-1;
            }
            if(data[i]==1)
            {
                count--;
            }
            if(count%2 == data[i])
            {
                parities[c]=0;
            }
            else if(count%2 != data[i])
            {
                parities[c]=1;
            }
            c++;
        }
    }
    for(int i=(rbit);i>=0;i--)
    {
        printf("%d ",parities[i]);
    }
    printf("\n");
    c=0;
    for(int i=0;i<rbit;i++)
    {
        c+=parities[i]*((int)pow(2,i));
    }
    if(c==0)
    {
        printf("No Error!\n");
        exit(0);
    }
    printf("Error at position : %d\n",c);
    data[c]=data[c]==0 ? 1 : 0;
    printf("Code after error correction is: ");
    for(i=(m_size+rbit);i>=1;i--)
        printf("%d ",data[i]);
    printf("\n");

    return 0;
}


// 1 0 1 1 0 0 1
// 1 0 1 0 0 0 0 1 1 1 0