#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>
#include<arpa/inet.h>

int main(int argc,char* argv[])
{

    int ser_sock,clnt_sock;
    struct sockaddr_in sock_adr,clnt_adr;

    ser_sock=socket(PF_INET,SOCK_STREAM,0);

    ser_adr.sin_family=AF_INET;
    ser_adr.sin_addr.s_addr=htonl(INADDR_ANY);
    ser_adr.sin_port=htons(atoi(argv[1]));

    

}