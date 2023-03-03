#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>

#define SIZE 1024*1024
void error_handling(char * msg)
{
    fputs(msg,stderr);
    fputc('\n',stderr);
    exit(1);
}

int main(int argc,char* argv[])
{
    int snd_buf=SIZE,rcv_buf=SIZE,state,sock;
    int res;
    socklen_t len=sizeof(res);

    sock=socket(PF_INET,SOCK_STREAM,0);
    if(state=setsockopt(sock,SOL_SOCKET,SO_SNDBUF,(void*)&snd_buf,sizeof(snd_buf))==-1)
        error_handling("set sen_buf size error!");
    else
        printf("set snd_buf successfully! \n");

    if(state=setsockopt(sock,SOL_SOCKET,SO_RCVBUF,(void*)&rcv_buf,sizeof(rcv_buf))==-1)
        error_handling("set rcv_buf size error!");
    else
        printf("set rcv_buf size successfully! \n");

    if(state=getsockopt(sock,SOL_SOCKET,SO_SNDBUF,(void*)&res,&len)==-1)
        error_handling("get snd_buf size error!");
    else
        printf("snd_buf size is %d \n",res);

    if(state=getsockopt(sock,SOL_SOCKET,SO_RCVBUF,(void*)&res,&len)==-1)
        error_handling("get rcv_buf size error!");
    else
        printf("get rcv_buf size is %d \n",res);



}



