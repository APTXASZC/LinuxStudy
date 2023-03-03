#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
void error_handling(char* message);

int main(int argc,char* argv[])
{
    int ser_sock;   // 客户端和服务器通信必然需要标识符，这里先做声明
    int clnt_sock;

    struct sockaddr_in ser_addr;    // 客户端和服务端都必须的IPv4地址结构体
    struct sockaddr_in clnt_addr;

    socklen_t clnt_addr_size;   // 

    char msg[]="hello worldasioduoahuonauovbueonifanoivnsdhvusdnianuvnubduvhoajifjaiofjaoij o98k";   // 服务端要返回的数据
    if(argc!=2){    // 判定是否调用格式有误
        printf("usage : %s <port> \n",argv[0]);
        exit(1);
    }

    ser_sock=socket(PF_INET,SOCK_STREAM,0);    // SOCK_STREAM : 面向连接的套接字(TCP)
                                               // PF_INET : IPv4协议族
                                               // 第三个参数通常为0，除非一个协议族出现多个传输类型，此时需要指定IPPROTO_TCP or IPPROTO_UDP
    if( ser_sock==-1 ){
        error_handling("socket() error!");
    }

    memset(&ser_addr,0,sizeof(ser_addr));
    ser_addr.sin_family=AF_INET;
    ser_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    ser_addr.sin_port=htons(atoi(argv[1]));

    if(bind(ser_sock,(struct sockaddr*)&ser_addr,sizeof(ser_addr))==-1){
        error_handling("bind() error!");
    }

    if(listen(ser_sock,5)==-1){         // 5表示服务端可以监听的个数
        error_handling("listen() error!");
    }

    clnt_addr_size=sizeof(clnt_addr);
    clnt_sock=accept(ser_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size);
    if(clnt_sock==-1){
        error_handling("accept() error!");
    }

    write(clnt_sock,msg,sizeof(msg));
    close(clnt_sock);
    close(ser_sock);

    return 0;

}

void error_handling(char* message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}