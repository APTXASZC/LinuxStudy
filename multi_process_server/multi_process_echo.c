#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>
#include<arpa/inet>

#define BUF_SIZE 30

void error_handling(char* msg);
void child(int sig);

int main(int argc,char* argv[])
{
    int serv_sock,clnt_sock;
    struct sockaddr_in ser_adr,clnt_adr;

    pid_t pid;
    struct sigaction act;
    socklen_t adr_sz;
    int str_len,state;

    char buf[BUF_SIZE];
    





    return 0;
}