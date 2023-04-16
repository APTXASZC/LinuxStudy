#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/time.h>
#include<sys/select.h>
#include<arpa/inet.h>
#include<unistd.h>

#define SIZE 30

void error_handling(char* msg)
{
    fputs(msg,stderr);
    fputc('\n',stderr);
    exit(1);
}
int main(int argc,char *argv[])
{
    int ser_sock,clnt_sock,fd_num,fd_max,str_len;
    char buf[SIZE];
    struct sockaddr_in ser_adr,clnt_adr;
    struct timeval timeout;
    fd_set reads,cpy_reads;
    socklen_t clnt_len;

    ser_sock=socket(PF_INET,SOCK_STREAM,0);
    memset(&ser_adr,0,sizeof(ser_adr));
    ser_adr.sin_family=AF_INET;
    ser_adr.sin_addr.s_addr=htonl(INADDR_ANY);
    ser_adr.sin_port=htons(atoi(argv[1]));

    if(bind(ser_sock,(struct sockaddr*)&ser_adr,sizeof(ser_adr))==-1)
        error_handling("bind error!");

    if(listen(ser_sock,5)==-1)
        error_handling("listen error!");

    fd_max=ser_sock;
    FD_ZERO(&reads);
    FD_SET(ser_sock,&reads);

    while(1)
    {
        cpy_reads=reads;
        timeout.tv_sec=5;
        timeout.tv_usec=5000;

        fd_num=select(fd_max+1,&cpy_reads,0,0,&timeout);
        
        if(fd_num==-1)
            error_handling("select error!");
        else if(fd_num==0)
            continue;
        for(int i=0;i<fd_max+1;++i)
        {
            if(FD_ISSET(i,&cpy_reads))
            {
                if(i==ser_sock)
                {
                    clnt_len=sizeof(clnt_adr);
                    clnt_sock=accept(ser_sock,(struct sockaddr*)&clnt_adr,&clnt_len);
                    if(clnt_sock==-1)
                        error_handling("accept error!");
                    
                    if(clnt_sock>fd_max)
                        fd_max=clnt_sock;
                    
                    FD_SET(clnt_sock,&reads);
                }
                else
                {
                    str_len=read(i,buf,SIZE);
                    if(str_len==0)
                    {
                        FD_CLR(i,&reads);
                        close(i);
                    }
                    else
                    {
                        write(i,buf,str_len);
                    }
                }
            }
        }
    }
    close(ser_sock);
    return 0;

}