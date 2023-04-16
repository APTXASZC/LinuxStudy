#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>

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
    printf("join in process! \n");

    sock=socket(PF_INET,SOCK_STREAM,0);

    memset(&adr,0,sizeof(adr));
    adr.sin_family=AF_INET;
    adr.sin_addr.s_addr=inet_addr(argv[1]);
    adr.sin_port=htons(atoi(argv[2]));

    if(connect(sock,(struct sockaddr*)&adr,sizeof(adr))==-1)
        error_handling("connect error!");

    sleep(0.5);
    write(sock,"123",strlen("123"));
    sleep(0.5);
    send(sock,"4",strlen("4"),MSG_OOB);
    sleep(0.5);
    write(sock,"56",strlen("56"));
    sleep(0.5);
    send(sock,"789",strlen("789"),MSG_OOB);

    close(sock);

    return 0;

}