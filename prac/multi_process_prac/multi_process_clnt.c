#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>
#include<arpa/inet.h>
#include<string.h>

#define SIZE 30

int main(int argc,char* argv[])
{

    int sock;
    struct sockaddr_in ser_adr;
    char buf[SIZE];

    sock=socket(PF_INET,SOCK_STREAM,0);

    memset(&ser_adr,0,sizeof(ser_adr));
    ser_adr.sin_family=AF_INET;
    ser_adr.sin_addr.s_addr=inet_addr(argv[1]);
    ser_adr.sin_port=htons(atoi(argv[2]));

    connect(sock,(struct sockaddr*)&ser_adr,sizeof(ser_adr));

    while(1)
    {
        puts("input info to send: ");
        fgets(buf,SIZE,stdin);

        if( !strcmp(buf,"q\n") || !strcmp(buf,"Q\n"))
            break;

        int rcv_len,msg_len;
        msg_len=write(sock,buf,sizeof(buf));
        while(msg_len>0){
            msg_len-=read(sock,buf,SIZE);
        }

        printf("receive info is : %s \n",buf);

    }

    close(sock);



    return 0;
}