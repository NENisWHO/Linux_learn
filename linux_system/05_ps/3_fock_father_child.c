/*************************************************************************
	> File Name: 3_fock_father_child.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月21日 星期日 14时55分06秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>


//区分父子进程
int main(void) {

    pid_t pid = -1;

    //创建一个子进程
    pid = fork();
    //fork函数在子进程中返回0,在父进程中返回子进程的pid
    if(pid == 0) {
        printf("hello itcast pid: %d ppid: %d\n", getpid(), getppid());
        //退出子进程
        exit(0);
    }else if(pid > 0) {
        printf("hello world pid: %d cpid: %d\n", getpid(), pid);
    }else if(pid < 0) {
        perror("fork");
        return 1;
    }

    return 0;
}
