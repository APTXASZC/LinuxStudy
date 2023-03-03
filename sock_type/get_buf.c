#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
void error_handling(char* msg);

int main(int argv,char* argc[])
{
    int sock;
    int rec_len,snd_len,state;
    socklen_t len;


    sock=socket(PF_INET,SOCK_STREAM,0);
    if(sock==-1)
        error_handling("sock create fail! \n");
    len=sizeof(snd_len);
    if(state=getsockopt(sock,SOL_SOCKET,SO_SNDBUF,(void*)&snd_len,&len)==-1)
        error_handling("getsockopt failed\n");
    printf("输出缓冲区大小为: %d \n",snd_len);
    len=sizeof(rec_len);
    state=getsockopt(sock,SOL_SOCKET,SO_RCVBUF,(void*)&rec_len,&len);
    if(state==-1)
        error_handling("getsockopt failed\n");
    printf("输入缓冲区大小为: %d \n",rec_len);

    return 0;
}
void error_handling(char* msg)
{
    fputs(msg,stderr);
    fputc('\n',stderr);
    exit(1);
}