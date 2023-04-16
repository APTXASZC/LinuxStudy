#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/signal.h>
#include<fcntl.h>
#include<netinet/in.h>

#define SIZE 30

void error_handling(char* msg)
{
    fputs(msg,stderr);
    fputc('\n',stderr);
    exit(1);
}
int accept_sock;
int recv_sock;
void urgent(int sig)
{
    if(sig==SIGURG){
    char buf[SIZE];
    int str_len;
    str_len=recv(recv_sock,buf,SIZE-1,MSG_OOB);
    buf[str_len]=0;
    printf("recv OOB info is %s \n",buf);
    }
}

int main(int argc,char * argv[])
{
    int str_len,state,recv_len;
    struct sockaddr_in accept_adr,recv_adr;
    struct sigaction act;
    char buf[SIZE];

    printf("join in process! \n");

    accept_sock=socket(PF_INET,SOCK_STREAM,0);
    
    memset(&accept_adr,0,sizeof(accept_adr));
    accept_adr.sin_family=AF_INET;
    accept_adr.sin_addr.s_addr=htonl(INADDR_ANY);
    accept_adr.sin_port=htons(atoi(argv[1]));

    act.sa_handler=urgent;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    
    if(bind(accept_sock,(struct sockaddr*)&accept_adr,sizeof(accept_adr))==-1)
        error_handling("bind error!");

    if(listen(accept_sock,5)==-1)
        error_handling("listen error!");

    

    recv_len=sizeof(recv_adr);
    recv_sock=accept(accept_sock,(struct sockaddr*)&recv_adr,&recv_len);
    
    state=sigaction(SIGURG,&act,0);
    fcntl(recv_sock,F_SETOWN,getpid());


    

    while((str_len=recv(recv_sock,buf,sizeof(buf),0))!=0)
    {
        if(str_len==-1)
            continue;
        buf[str_len]=0;
        puts(buf);
    }
    close(recv_sock);
    close(accept_sock);
    return 0;
}