/*************************************************************************
	> File Name: 7_orphan.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月21日 星期日 17时22分43秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

//僵尸进程：子进程退结束了，父进程没有回收其资源
int main(void) {
    
    pid_t pid = -1;

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    //子进程
    if (0 == pid) {
        for (int i = 0; i < 5; i++) {
            printf("子进程做事 %d\n", i);
            sleep(1);
        }
        printf("子进程想不开了，结束了自己...\n");
        //子进程退出
        exit(0);
    }
    
    //父进程getchar后才退出
    //getchar();
    
    sleep(100);
    printf("父进程睡醒了，父进程退出...\n");
    return 0;
}
