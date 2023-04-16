#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

#define SIZE 30

void error_handling(char* msg)
{
    fputs(msg,stderr);
    fputc('\n',stderr);
    exit(1);
}

int main(int argc,char* argv[])
{
    int sock,str_len;
    struct sockaddr_in adr;
    char buf[SIZE];

    sock=socket(PF_INET,SOCK_STREAM,0);
    memset(&adr,0,sizeof(adr));
    adr.sin_family=AF_INET;
    adr.sin_addr.s_addr=inet_addr(argv[1]);
    adr.sin_port=htons(atoi(argv[2]));

    if(connect(sock,(struct sockaddr*)&adr,sizeof(adr))==-1)
        error_handling("connect error!");
    else
        puts("connect ....");

    while(1)
    {
        fputs("please input info to echo (q or Q to quit): ",stdout);
        fgets(buf,SIZE,stdin);

        if( !strcmp(buf,"q\n") || !strcmp(buf,"Q\n"))
            break;

        str_len=write(sock,buf,sizeof(buf));
        while(str_len>0)
            str_len-=read(sock,buf,SIZE);
        
        printf("the info you receive is %s ",buf);
    }
    close(sock);
    return 0;
}