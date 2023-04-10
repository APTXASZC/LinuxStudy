#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>
#include<arpa/inet.h>
#include<string.h>

#define SIZE 30


void error_handling(char* msg);
void child(int sig);

int main(int argc,char* argv[])
{
    // general component
    pid_t pid;
    char buf[SIZE];


    // network component
    int ser_sock,clnt_sock;
    struct sockaddr_in ser_adr,clnt_adr;

    ser_sock=socket(PF_INET,SOCK_STREAM,0);

    memset(&ser_adr,0,sizeof(ser_adr));
    ser_adr.sin_family=AF_INET;
    ser_adr.sin_addr.s_addr=htonl(INADDR_ANY);
    ser_adr.sin_port=htons(atoi(argv[1]));

    if(bind(ser_sock,(struct sockaddr*)&ser_adr,sizeof(ser_adr))==-1)
        error_handling("bind error!");
    
    // signal component
    struct sigaction act;
    act.sa_handler=child;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;

    sigaction(SIGCHLD,&act,0);

    
    if(listen(ser_sock,5) == -1)
        error_handling("listen error!");

    
    while(1)
    {
        int clnt_len=sizeof(clnt_adr);
        clnt_sock=accept(ser_sock,(struct sockaddr*)&clnt_sock,&clnt_len);
        if(clnt_sock == -1){
            continue;
        }
        else
        {
            printf("connect successfully! \n");
        }

        int strlen;
        pid=fork();

        if(pid == -1){
            error_handling("process create error!");
        }
        else if(pid == 0){
            close(ser_sock);
            while((strlen=read(clnt_sock,buf,SIZE)) != 0)
            {
                printf("receive info is %s",buf);
                write(clnt_sock,buf,strlen);
            }
            close(clnt_sock);
            
            puts("the client will disconnect !");
            return 0;
        }
        else
        {
            close(clnt_sock);
        }
        
        
    }

    close(ser_sock);


    




}













void child(int sig){
    if(sig == SIGCHLD){
        pid_t pid;
        int state;
        pid=waitpid(-1,&state,WNOHANG);
        if(WIFEXITED(state)){
            printf("child process was exited successfully ,and its return val is %d \n",WEXITSTATUS(state));
        }
    }
}
void error_handling(char* msg){
    fputs(msg,stderr);
    fputc('\n',stderr);
    exit(1);
}