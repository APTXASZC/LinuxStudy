#include<stdio.h>
#include<sys/uio.h>
#define SIZE 100

int main(int argc,char* argv[])
{
    struct iovec vec[2];
    int str_len;
    char buf1[SIZE]={0,};
    char buf2[SIZE]={0,};

    vec[0].iov_base=buf1;
    vec[0].iov_len=5;

    vec[1].iov_base=buf2;
    vec[1].iov_len=SIZE;

    str_len=readv(0,vec,2);
    printf("read bytes :%d \n",str_len);
    printf("first message : %s \n",buf1);
    printf("second msg : %s \n",buf2);

    return 0;
}