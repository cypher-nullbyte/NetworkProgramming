#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>


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
    
    printf("%lld",binary);
    
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

int main()
{
    int bin[]={0,1,1,0,1,0,0,0};
    char* hex=binToHex(bin,8);
    printf("\n%s",hex);
}