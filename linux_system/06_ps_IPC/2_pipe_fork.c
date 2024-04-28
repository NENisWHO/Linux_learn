/*************************************************************************
	> File Name: 2_pipe_fork.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月22日 星期一 08时20分36秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

#define SIZE 128

//父子进程使用无名管道通信
int main(void) {
    
    //在fork之期创建管道，因为子进程会遗传父进程的文件描述符
    //父进程写管道，关掉父进程管道读段；子进程读管道，关闭子进程写端
    int ret = -1;
    pid_t pid = -1;
    int fds[2];
    char buf[SIZE];

    //1.创建无名管道
    ret =  pipe(fds);
    if (ret == -1) {
        perror("pipe");
        return 1;
    }
    
    //2.创建子进程
    pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    //子进程 读管道
    if (pid == 0) {
        //关闭写端
        close(fds[1]);
    
        memset(buf, 0, SIZE);
        //读取管道内容
        ret = read(fds[0], buf, SIZE);
        if (ret < 0) {
            perror("read");
            exit(-1);
        }
        printf("child process buf: %s\n", buf);
        //关闭读端
        close(fds[0]);
        //退出进程
        exit(0);
    }

    //父进程写管道
    //关闭读端
    close(fds[0]);
    //写管道        
    ret = write(fds[1], "ABCDEFGHIJK", 10);
    if (ret < 0) {
        perror("write");
        return 1;
    }
    printf("parent process write len: %d\n", ret);
    //关闭写段
    close(fds[1]);

    return 0;
}
