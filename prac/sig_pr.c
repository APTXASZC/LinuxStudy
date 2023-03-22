#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>

void inter(int sig){
    if(sig == SIGINT){
        printf("进程被强行终止！ \n");
    }
}
void alrm(int sig){
    if(sig == SIGALRM){
        printf("进程被alarm信号终止\n");
        alarm(2);
    }
}

void child(int sig){
    if(sig == SIGCHLD){
        printf("有子进程终止了 \n");
        int state;
        pid_t pid=waitpid(-1,&state,WNOHANG);
        if(!WIFEXITED(state)){
            printf("子进程未正确退出! \n");
            return ;
        }
        printf("子进程正确退出了,其进程id为: %d , 返回值为 %d\n ",pid,WEXITSTATUS(state));
    }
}


int main(int argc,char* argv[]){

    int id,state;

    struct sigaction ac1,ac2,ac3;

    ac1.sa_handler=inter;
    ac2.sa_handler=alrm;
    ac3.sa_handler=child;

    sigemptyset(&ac1.sa_mask);
    sigemptyset(&ac2.sa_mask);
    sigemptyset(&ac3.sa_mask);

    ac1.sa_flags=0;
    ac2.sa_flags=0;
    ac3.sa_flags=0;

    sigaction(SIGINT,&ac1,0);
    sigaction(SIGALRM,&ac2,0);
    sigaction(SIGCHLD,&ac3,0);




    id=fork();

    if(id==0){
        printf("现在进入子进程,over,进程");
        return 20;
    }
    else{
        for(int i=0;i<3;++i){
            printf("现在第%d次进入sleep状态... \n",i);
            sleep(50);
        }
    }

    


    return 0;



}