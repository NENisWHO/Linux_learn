/*************************************************************************
	> File Name: 2_daemon.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月25日 星期四 16时38分10秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

//创建守护进程
int main(void) {
    int ret = -1;
    pid_t pid = -1;
    //1. 创建子进程，父进程退出 --> 形式上脱离控制终端
    pid = fork();
    if (-1 == pid) {
        perror("fork");
        return 1;
    }
    if (pid > 0) {
        //父进程退出
        exit(0);
    }

    //2. 创建新的会话 --> 完全脱离控制终端
    pid = setsid();
    if (-1 == pid) {
        perror("setsid");
        return 1;
    }   
    //3. 改变当前工作目录 --> 防止占用可卸载的文件系统
    ret = chdir("/");
    if (-1 == ret) {
        perror("chdir");
        return 1;
    }
    //4. 设置权限掩码
    umask(0);

    //5. 关闭文件描述符
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    //6. 执行核心的任务
    //每隔一秒钟输出当前时间到/tmp/txt.log 文件中
    int i = 0;
    while(1) {
        system("date >> /tmp/txt.log");
        sleep(1);
        i++;
        if(0 == i % 9) {
            system("date > /tmp/txt.log");
        }
        if (i == 100) {
            i = 0;
        }
    }
    return 0;
}
