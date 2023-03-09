#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>


int gval=10;
int main()
{
    pid_t pid;
    int lval=20;
    pid=fork();

    if(pid==0){
        printf("现在是子进程[%d %d] \n",gval+=2,lval+=2);
    }
    else
    {
        printf("现在是父进程[%d %d] \n",gval-=2,lval-=2);
    }
    return 0;

}