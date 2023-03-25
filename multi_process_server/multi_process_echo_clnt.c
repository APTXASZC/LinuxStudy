#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>
#include<arpa/inet.h>
#include<string.h>

#define BUF_SIZE 30

int main(int argc,char* argv[])
{
    int sock;
    struct sockaddr_in ser_adr;

    char message[BUF_SIZE];

    sock=socket(PF_INET,SOCK_STREAM,0);

    memset(&ser_adr,0,sizeof(ser_adr));
    ser_adr.sin_family=AF_INET;
    ser_adr.sin_addr.s_addr=inet_addr(argv[1]);
    ser_adr.sin_port=htons(atoi(argv[2]));

    if(connect(sock,(struct sockaddr*)&ser_adr,sizeof(ser_adr))==-1)
        {
            printf("connec error \n");
            exit(1);
        }
    
    while(1){
        printf("现在进入客户端了，请输入要发送的信息(退出请输入q or Q):  ");
        fgets(message,BUF_SIZE,stdin);
        
        if( strcmp(message,"Q\n")==0 || strcmp(message,"q\n")==0 )
            break;

        int rcv_len,clnt_len=0;

        rcv_len=write(sock,message,strlen(message));
        
        while(clnt_len<clnt_len){
            clnt_len+=read(sock,message,BUF_SIZE);
        }

        printf("fuck the value is %s returned \n",message);
    }


    close(sock);
    



    return 0;
}