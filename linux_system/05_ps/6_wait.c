/*************************************************************************
> File Name: 6_wait.c
> Author: 
> Mail: 
> Created Time: 2024年04月21日 星期日 16时41分49秒
************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main(void) {

    int status = 0;
    int i = 0;
    int ret = -1;
    pid_t pid = -1;

    //创建子进程
    pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }else if (pid == 0) {
        for (i; i < 10; i++) {
            printf("child process do thing %d, pid(%d)\n", i + 1, getpid());
            sleep(1);
        }
        //子进程终止
        exit(10);
    }

    //父进程执行
    printf("父进程等待子进程退出，回收其资源\n");
    //父进程阻塞，等待子进程退出
    ret = wait(&status);
    if (-1 == ret) {
        perror("wait");
        return 1;
    }
    printf("父进程收回子进程资源...\n");

    //属于正常退出
    if (WIFEXITED(status)) {
        printf("子进程退出状态码：%d\n", WEXITSTATUS(status));
    }else if (WIFSIGNALED(status)) {
        //kill -9 pid
        printf("子进程被信号%d杀死了...\n", WTERMSIG(status));
    }else if (WIFSTOPPED(status)) {
        //kill -19 pid 暂停   kill -18 pid 恢复
        printf("子进程被信号%d暂停...\n",WSTOPSIG(status));
    }

    return 0;
}
