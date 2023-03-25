#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>
#include<arpa/inet.h>
#include<string.h>

#define BUF_SIZE 30

void error_handling(char* msg);
void child(int sig);

int main(int argc,char* argv[])
{
    int serv_sock,clnt_sock;
    struct sockaddr_in ser_adr,clnt_adr;

    // sock以及sock addr的部分

    serv_sock=socket(PF_INET,SOCK_STREAM,0);

    memset(&ser_adr,0,sizeof(ser_adr));
    ser_adr.sin_family=AF_INET;
    ser_adr.sin_addr.s_addr=htonl(INADDR_ANY);
    printf("%d \n",INADDR_ANY);
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
    sigaction(SIGCHLD,&act,0);

    int adr_len=sizeof(ser_adr);

    if(bind(serv_sock,(struct sockaddr*)&ser_adr,adr_len)==-1)
        error_handling("bind error! \n ");

    if(listen(serv_sock,5)==-1)
        error_handling("listen error ! \n");

    while(1){

        int clnt_size=sizeof(clnt_adr);
        clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_adr,&clnt_size);
        if(clnt_sock==-1)
            continue;
        else
            puts("new client connected ! ");

        pid=fork();
        if(pid==-1){
            close(clnt_sock);
            continue;
        }
        if(pid==0){
            close(serv_sock);
            while((str_len=read(clnt_sock,buf,BUF_SIZE))!=0)
                write(clnt_sock,buf,sizeof(buf));
            printf("receive info is %s",buf);
            close(clnt_sock);
            puts("client disconnected...");
            return 0;
        }
        else 
        {
            close(clnt_sock);
            printf("现在是父进程! \n");
        }

    }
    close(serv_sock);
    return 0;

    


}

void error_handling(char* msg){
    fputs(msg,stderr);
    fputc('\n',stderr);
    exit(1);
}
void child(int sig){
    pid_t pid;
    int status;
    pid=waitpid(-1,&status,WNOHANG);
    printf("removed proc id: %d \n",pid);
}