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

void chld(int sig){
    if(sig==SIGCHLD){
        int state;
        pid_t id=waitpid(-1,&state,WNOHANG);
        if(WIFEXITED(state)){
        printf("child process is dead,it's pid is %d \n",id);
        printf("exit send state %d \n",WEXITSTATUS(state));
        }
    }
}

int main(int argc,char* argv[])
{
    struct sigaction act;

    act.sa_handler=timeout;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;

    struct sigaction act2;
    act2.sa_handler=inter;
    sigemptyset(&act2.sa_mask);
    act2.sa_flags=0;

    struct sigaction act3;
    act3.sa_handler=chld;
    act3.sa_flags=0;
    sigemptyset(&act3.sa_mask);

    sigaction(SIGCHLD,&act3,0);
    sigaction(SIGINT,&act2,0);
    sigaction(SIGALRM,&act,0);

    alarm(2);



    /*for(int i=0;i<3;++i){
        printf("开始进入 alarm sig 处理,等待100s\n");
        sleep(100);
    } */

    alarm(0);

    pid_t id=fork();
    if(id==0){
        printf("now is chld process ,my pid is %d \n",getpid());
        return 20;
    }
    else{
        pid_t t=id;
        printf("child process id is %d \n",id);

        for(int i=0;i<5;++i){
            printf("wait some times ! \n");
            sleep(5);
        }

    }




    return 0;
}