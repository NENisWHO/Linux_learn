/*************************************************************************
	> File Name: 1_kill.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月23日 星期二 09时42分11秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<signal.h>

//signal: kill()
int main(void) {
   
    pid_t pid = -1;

    //创建一个子进程
    pid = fork();
    if (-1 == pid) {
        perror("fork");
        return 1;
    }
    //子进程
    if (pid == 0 ) {
        while (1) {
            printf("child process do work...\n");
            sleep(1);
        }
        //退出进程
        exit(0);
    }else {
        //父进程
        sleep(3);
        printf("子进程，该退出了...\n");
        kill(pid, SIGTERM);
        printf("父进程该结束了，已经完成了他的使命\n");
    }

    return 0;
}
