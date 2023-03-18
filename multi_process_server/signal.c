#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>

void timeout(int sig){
    if(sig == SIGALRM){
        puts("timeout fk u! \n");
        alarm(2);
    }
}

void inter(int sig){
    if(sig == SIGINT){
        puts("CTRL + C is pressed! \n");
    }
}


int main(int argc,char * argv[])
{

    signal(SIGALRM,timeout);
    signal(SIGINT,inter);

    alarm(2);

    for(int i=0;i<3;++i){
        printf("please wait for 100 secs! \n");
        sleep(100);
    }

    return 0;




    return 0;
}