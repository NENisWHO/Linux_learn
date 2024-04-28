/*************************************************************************
	> File Name: 2.fock.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月21日 星期日 08时27分10秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

//创建一个子进程
int main(void) {
    //创建子进程
    fork();
    
    printf("hello world\n");
    printf("getpid: %d\n", getpid());
    printf("getppid: %d\n", getppid());
    return 0;
}
