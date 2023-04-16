#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define SIZE 30

void error_hadnling(char* msg)
{
    fputs(msg,stderr);
    fputc('\n',stderr);
    exit(1);
}
int ser_sock;
int clnt_sock;

int main(int argc,char* argv[])
{
    int str_len;
    socklen_t clnt_len;
    char buf[SIZE];
    struct sockaddr_in ser_adr,clnt_adr;

    ser_sock=socket(PF_INET,SOCK_STREAM,0);

    memset(&ser_adr,0,sizeof(ser_adr));
    ser_adr.sin_family=AF_INET;
    ser_adr.sin_addr.s_addr=htonl(INADDR_ANY);
    ser_adr.sin_port=htons(atoi(argv[1]));

    if(bind(ser_sock,(struct sockaddr*)&ser_adr,sizeof(ser_adr))==-1)
        error_hadnling("connect error");

    if(listen(ser_sock,5)==-1)
        error_hadnling("listen error");

    clnt_len=sizeof(clnt_adr);
    clnt_sock=accept(ser_sock,(struct sockaddr*)&clnt_adr,&clnt_len);

    while(1)
    {
        str_len=recv(clnt_sock,buf,SIZE-1,MSG_PEEK|MSG_DONTWAIT);
        if(str_len>0) break;
    }

    buf[str_len]=0;
    printf("msg %d bytes : %s \n",str_len,buf);

    str_len=recv(clnt_sock,buf,SIZE-1,0);
    buf[str_len]=0;

    printf("msg %d bytes : %s \n",str_len,buf);

    close(clnt_sock);
    close(ser_sock);

    return 0;
    

}