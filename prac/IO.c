#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/tcp.h>

int main(int argv,char* argc[])
{
    int sock,state;
    int len=sizeof(state);

    sock=socket(PF_INET,SOCK_STREAM,0);

    getsockopt(sock,IPPROTO_TCP,TCP_NODELAY,(void*)&state,&len);

    printf("default Nagle algo is %d\n",state);

    state=1;

    setsockopt(sock,IPPROTO_TCP,TCP_NODELAY,(void*)&state,len);

    printf("after set Nagle algo is %d \n",state);

    
    


    
    


    return 0;
}