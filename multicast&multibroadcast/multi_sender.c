#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<string.h>

#define TTL 64
#define SIZE 30

void error_handling(char * msg)
{
    fputs(msg,stderr);
    fputc('\n',stderr);
    exit(1);
}

int main(int argc,char * argv[])
{
    int sock;
    struct sockaddr_in adr;
    
    sock=socket(PF_INET,SOCK_DGRAM,0);

    memset(&adr,0,sizeof(adr));
    adr.sin_family=AF_INET;
    adr.sin_addr.s_addr=inet_addr(argv[1]);
    adr.sin_port=htons(atoi(argv[2]));

    

}