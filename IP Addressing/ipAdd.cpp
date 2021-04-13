#include<iostream>
#include<string>
#include<sstream>
#include<stdio.h>
using namespace std;

class IPAddress {
public:
 const string validIPv6Chars = "0123456789abcdefABCDEF";
 const string digits = "0123456789";
    bool isValidIPv4Block(string& block) {
        int num = 0;
        //check 
        if (block.size() > 0 && block.size() <= 3) {
            for (int i = 0; i < block.size(); i++) {
                char c = block[i];
                // check value
                if (digits.find(c)== string::npos || (i == 0 && c == '0' && block.size() > 1))  // special case: if c is a leading zero
                return false;
                else {
                num *= 10;
                num += c - '0';
                }
            }
            return num <= 255;
        }
        return false;
    }

    bool isValidIPv6Block(string& block) {
        //check length
        if (block.size() > 0 && block.size() <= 4) {
            for (int i = 0; i < block.size(); i++) {
                char c = block[i];
                 // check value
                if (validIPv6Chars.find(c) == string::npos)
                    return false;
            }
            return true;
        }
        return false;
    }

    string validIPAddress(string IP) {
        stringstream ss(IP);
        string block;
        // ipv4 candidate
        if (IP.substr(0, 4).find('.') != string::npos) {
            for (int i = 0; i < 4; i++) {
            if (!getline(ss, block, '.') || !isValidIPv4Block(block))
                   return "Neither";
            }
            return ss.eof() ? "IPv4" : "Neither";
        }
        // ipv6 candidate
        else if (IP.substr(0, 5).find(':') != string::npos) {
            for (int i = 0; i < 8; i++) {
            if (!getline(ss, block, ':') || !isValidIPv6Block(block))
                return "Neither";
            }
            return ss.eof() ? "IPv6" : "Neither";
        }

        return "Neither";
    }
};

// Function to find out the Class
char findClass(char str[])
{
    // storing first octet in arr[] variable
    char arr[4];
    int i = 0;
    while (str[i] != '.')
    {
        arr[i] = str[i];
        i++;
    }
    i--;
  
    // converting str[] variable into number for
    // comparison
    int ip = 0, j = 1;
    while (i >= 0)
    {
        ip = ip + (str[i] - '0') * j;
        j = j * 10;
        i--;
    }
  
    // Class A
    if (ip >=1 && ip <=127)
        return 'A';
  
    // Class B
    else if (ip >= 128 && ip <= 191)
        return 'B';
  
    // Class C
    else if (ip >= 192 && ip <= 223)
        return 'C';
  
    // Class D
    else if (ip >= 224 && ip <= 239)
        return 'D';
  
    // Class E
    else
        return 'E';
}
  
// Function to separate Network ID as well as
// Host ID and print them
void separate(char str[], char ipClass)
{
    // Initializing network and host array to NULL
    char network[12], host[12];
    for (int k = 0; k < 12; k++)
        network[k] = host[k] = '\0';
  
    // for class A, only first octet is Network ID
    // and rest are Host ID
    if (ipClass == 'A')
    {
        int i = 0, j = 0;
        while (str[j] != '.')
            network[i++] = str[j++];
        i = 0;
        j++;
        while (str[j] != '\0')
            host[i++] = str[j++];
        printf("Network ID is %s\n", network);
        printf("Host ID is %s\n", host);
    }
  
    // for class B, first two octet are Network ID
    // and rest are Host ID
    else if (ipClass == 'B')
    {
        int i = 0, j = 0, dotCount = 0;
  
        // storing in network[] up to 2nd dot
        // dotCount keeps track of number of
        // dots or octets passed
        while (dotCount < 2)
        {
            network[i++] = str[j++];
            if (str[j] == '.')
                dotCount++;
        }
        i = 0;
        j++;
  
        while (str[j] != '\0')
            host[i++] = str[j++];
  
        printf("Network ID is %s\n", network);
        printf("Host ID is %s\n", host);
    }
  
    // for class C, first three octet are Network ID
    // and rest are Host ID
    else if (ipClass == 'C')
    {
        int i = 0, j = 0, dotCount = 0;
  
        // storing in network[] up to 3rd dot
        // dotCount keeps track of number of
        // dots or octets passed
        while (dotCount < 3)
        {
            network[i++] = str[j++];
            if (str[j] == '.')
                dotCount++;
        }
  
        i = 0;
        j++;
  
        while (str[j] != '\0')
            host[i++] = str[j++];
  
        printf("Network ID is %s\n", network);
        printf("Host ID is %s\n", host);
    }
  
    // Class D and E are not divided in Network
    // and Host ID
    else
        printf("In this Class, IP address is not divided into Network and Host ID\n");
}

int main()
{
    string input;
    cout<<"Enter a valid IP: ";
    cin>>input;
    IPAddress ip;
    string output=ip.validIPAddress(input);
    cout<<"The given IP Address is: "<<output<<"\n";
    if(output.compare("IPv4")!=0) exit(0);
    char ip4[input.size()+1];
    for(int i=0;i<input.size();i++) ip4[i]=(char)input[i];
    ip4[input.size()]='\0';
    char ipClass = findClass(ip4);
    printf("Given IP address belongs to Class %c\n",ipClass);
    separate(ip4, ipClass);
    return 0;
}

//2001:0db8:85a3:0:0:8a2e:0370:7334
//2001:0db8:85a3:0000:0000:8a2e:0370:7334