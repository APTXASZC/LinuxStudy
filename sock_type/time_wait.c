#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
void error_handling(char* msg)
{
    fputs(msg,stderr);
    fputc('\n',stderr);
    exit(1);
}
#define TRUE 1
#define FALSE 0

int main(int argv,char* argc[])
{
    int ser_sock,clnt_sock;
    char message[30];
    int option,str_len;
    socklen_t optlen,clnt_adr_sz;
    struct sockaddr_in ser_adr,clnt_adr;
    
    ser_sock=socket(PF_INET,SOCK_STREAM,0);

    optlen=sizeof(option);
    option=TRUE;
    setsockopt(ser_sock,SOL_SOCKET,SO_REUSEADDR,(void*)&option,optlen); // 获取要取址，设置不用
    // SO_REUSEADDR 可以让Time-wait状态下的套接字端口号重新分配给新的套接字(默认为0)

    memset(&ser_adr,0,sizeof(ser_adr));
    ser_adr.sin_family=AF_INET;
    ser_adr.sin_addr.s_addr=htonl(INADDR_ANY);
    ser_adr.sin_port=htons(atoi(argc[1]));

    if(bind(ser_sock,(struct sockaddr*)&ser_adr,sizeof(ser_adr))==-1)
        error_handling("bind error \n");

    if(listen(ser_sock,5)==-1)
        error_handling("listen error! \n");

    clnt_adr_sz=sizeof(clnt_adr);
    clnt_sock=accept(ser_sock,(struct sockaddr*)&clnt_adr,&clnt_adr_sz);

    while( str_len=read(clnt_sock,message,sizeof(message))!=0 ){
        write(clnt_sock,message,str_len);
        write(1,message,str_len);
    }
    close(clnt_sock);
    close(ser_sock);

    return 0;
}


