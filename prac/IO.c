#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>

int main(int argv,char* argc[])
{
    int sock,state;
    int res;
    socklen_t len=sizeof(res);

    sock=socket(PF_INET,SOCK_STREAM,0);
    //len=sizeof(res);
    if(state=getsockopt(sock,SOL_SOCKET,SO_SNDBUF,(void*)&res,&len)==-1){
        printf("getsockopt failed \n");
    }
    else{
        printf("snd_buf size is %d \n",res);
    }

    //len=sizeof(res);
    if(state=getsockopt(sock,SOL_SOCKET,SO_RCVBUF,(void*)&res,&len)==-1){
        printf("getsockopt failed\n");
    }
    else{
        printf("rcv_buf size is %d \n",res);
    }
    

    
    


    
    


    return 0;
}