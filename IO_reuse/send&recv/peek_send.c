#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>

#define SIZE 30

void error_hadling(char * msg)
{
    fputs(msg,stderr);
    fputc('\n',stderr);
    exit(1);
}

int main(int argc,char* argv[])
{
    int sock,str_len;
    char buf[SIZE];
    struct sockaddr_in adr;

    sock=socket(PF_INET,SOCK_STREAM,0);
    memset(&adr,0,sizeof(adr));
    adr.sin_family=AF_INET;
    adr.sin_addr.s_addr=inet_addr(argv[1]);
    adr.sin_port=htons(atoi(argv[2]));

    if(connect(sock,(struct sockaddr*)&adr,sizeof(adr))==-1)
        error_hadling("connect error");

    write(sock,"1234",strlen("1234"));

    close(sock);

    return 0;

}