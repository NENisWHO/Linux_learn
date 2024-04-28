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

//孤儿进程：父进程退出了，子进程还在执行
int main(void) {
    
    pid_t pid = -1;

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid > 0) {
        printf("父进程累了，休息1s\n");
        sleep(1);
        printf("还是太累了，先撤了\n");
        exit(0);
    }

    while(1) {
        //图形界面孤儿被托管的进程不是1, 非图形界面是1
        printf("子进程不停的工作 ppid：%d\n", getppid());
        sleep(1);
    }

    return 0;
}
