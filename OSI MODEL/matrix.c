#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int r;
    int c;
    int **k;
}Matrix;

void deallocate(Matrix *m)
{
    free(m->k);
    free(m);
}

Matrix* autoMatrix(int r,int c)
{
    Matrix* m=(Matrix*)malloc(sizeof(Matrix));
    m->r=r;m->c=c;
    int len=sizeof(int*)*m->r+sizeof(int)*m->r*m->c;
    m->k=(int **)malloc(len);
    int *ptr=(int *)(m->k+m->r);
    for(int i=0;i<m->r;i++)
    {
        m->k[i]=(int *)(ptr+i*m->c);
    }
    return m;
}

Matrix *mulMatrices(Matrix* m1,Matrix *m2)
{
    if(m1->c!=m2->r)
    {
        printf("Matrces are of imcompatiable dimensions for Multiplication!");
        deallocate(m1);
        deallocate(m2);
        exit(0);
    }
    Matrix *res=autoMatrix(m1->r,m2->c);
    for(int i=0;i<m1->r;i++)
    {
        for(int j=0;j<m2->c;j++)
        {
            for(int k=0;k<m1->c;k++)
                res->k[i][j]+=m1->k[i][k]*m2->k[k][j];
        }   
    }
    return res;
}

Matrix *subMatrices(Matrix* m1,Matrix *m2)
{
    if(m1->r!=m2->r || m1->c!=m2->c )
    {
        printf("Matrices should be of same dimension!");
        deallocate(m1);
        deallocate(m2);
        exit(0);
    }
    Matrix *res=autoMatrix(m1->r,m1->c);
    for(int i=0;i<res->r;i++)
    {
        for(int j=0;j<res->c;j++)
        {
            res->k[i][j]=m1->k[i][j]-m2->k[i][j];
        }   
    }
    return res;
}

Matrix *addMatrices(Matrix* m1,Matrix *m2)
{
    if(m1->r!=m2->r || m1->c!=m2->c )
    {
        printf("Matrices should be of same dimension!");
        deallocate(m1);
        deallocate(m2);
        exit(0);
    }
    Matrix *res=autoMatrix(m1->r,m1->c);
    for(int i=0;i<res->r;i++)
    {
        for(int j=0;j<res->c;j++)
        {
            res->k[i][j]=m1->k[i][j]+m2->k[i][j];
        }   
    }
    return res;
}
void matrixSizeFiller(Matrix *m)
{
    printf("Enter size of Matrix (row & col): ");
    scanf("%d%d",&m->r,&m->c);
}

Matrix* createMatrix()
{
    Matrix *m=(Matrix*)malloc(sizeof(Matrix));
    matrixSizeFiller(m);
    int len=sizeof(int*)*m->r+sizeof(int)*m->r*m->c;
    m->k=(int **)malloc(len);
    int *ptr=(int *)(m->k+m->r);
    for(int i=0;i<m->r;i++)
    {
        m->k[i]=(int *)(ptr+i*m->c);
    }
    printf("Enter the %dX%d Matrix:\n",m->r,m->c);
    for(int i=0;i<m->r;i++)
    {
        for(int j=0;j<m->c;j++)
            scanf("%d",(*(m->k+i)+j));
    }
    return m;
}
void printMatrix(Matrix *m)
{
    for(int i=0;i<m->r;i++)
    {
        for(int j=0;j<m->c;j++)
            printf("%d\t",m->k[i][j]);
        printf("\n");
    }
}

int main()
{   
    Matrix *m1=createMatrix();
    Matrix *m2=createMatrix();
    char choice;
    do
    {
        Matrix *m;
        printf("Enter Operation(+,-,*): ");
        scanf(" %c",&choice);
        switch(choice)
        {
            case '+':
                m=addMatrices(m1,m2);
                printf("Resultant Addition Matrix is: \n");
                printMatrix(m);
                break;
            case '-':
                m=subMatrices(m1,m2);
                printf("Resultant Subtraction Matrix is: \n");
                printMatrix(m);
                break;
            case '*':
                m=mulMatrices(m1,m2);
                printf("Resultant Multiplication Matrix is: \n");
                printMatrix(m);
                break;
            default:
                printf("Please Enter a valid choice!");
                exit(0);
        }
        deallocate(m);
        printf("Try other Operation (Y,N): ");
        scanf(" %c",&choice);
    }while(choice=='y' || choice=='Y');
    deallocate(m1);
    deallocate(m2);
    return 0;
}