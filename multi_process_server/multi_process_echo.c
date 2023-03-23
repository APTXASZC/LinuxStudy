#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>
#include<arpa/inet.h>

#define BUF_SIZE 30

void error_handling(char* msg);
void child(int sig);

int main(int argc,char* argv[])
{
    int serv_sock,clnt_sock;
    struct sockaddr_in ser_adr,clnt_adr;

    // sock以及sock addr的部分

    serv_sock=socket(PF_INET,SOCK_STREAM,0);

    ser_adr.sin_family=AF_INET;
    ser_adr.sin_addr.s_addr=htol(INADDR_ANY);
    ser_adr.sin_port=htons(atoi(argv[1]));

    // signal以及process部分
    pid_t pid;
    struct sigaction act;
    socklen_t adr_sz;
    int str_len,state;

    char buf[BUF_SIZE];

    act.sa_handler=child;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    // 注册interupt信号
    sigaction(SIGINT,&act,0);

    int adr_len=sizeof(ser_adr);

    if(bind(ser_sock,(struct sockaddr*)&ser_sock,adr_len)==-1)
        error_handling("bind error! \n ");

    




    




    return 0;
}