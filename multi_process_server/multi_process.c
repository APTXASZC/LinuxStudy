#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/wait.h>


int gval=10;
int main()
{
    int state;
    pid_t pid=fork();

    if(pid==0){
        sleep(15);
        exit(10);
    }
    else{
        printf("child pid is : %d \n",pid);

        if(!waitpid(-1,&state,WNOHANG)){
            sleep(3);
            printf("sleep 3secs ! \n");
        }

        if(WIFEXITED(state))
            printf("normal exited !  %d \n",WEXITSTATUS(state));
    }

    

    return 0;

}