/*************************************************************************
	> File Name: 01_getpid.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月21日 星期日 08时11分49秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

//获取进程号 父进程号 进程组号
int main(void) {

    pid_t pid = -1;
    //获取当前进程的进程号
    pid = getpid();
    printf("进程号：%d\n", pid);

    //获取当前进程的父进程号
    pid = getppid();
    printf("父进程：%d\n", pid);

    //获取当前进程的进程组号
    pid = getpgid(getpid()) ;
    printf("进程组号：%d\n", pid);

    return 0;
}
