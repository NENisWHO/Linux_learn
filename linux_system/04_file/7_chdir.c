/*************************************************************************
	> File Name: 7_chdir.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月20日 星期六 15时34分33秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>


#define SIZE 32

//getcwd chdir
int main(void) {
    int ret = -1;
    char buf[SIZE];

    //1.获取当前进程的工作目录
    memset(buf, 0, SIZE);
    if(NULL == getcwd(buf, SIZE)){
        perror("getcwd");
        return 1;
    }
    printf("buf = %s\n", buf);
    //2.改变当前进程的工作目录
    ret = chdir("/home/learn/linux_system");
    if(-1 == ret) {
        perror("chdir");
        return 1;
    }
    //3.获取当前进程的工作目录
    memset(buf, 0, SIZE);
    if(NULL == getcwd(buf, SIZE)) {
        perror("getcwd");
        return 1;
    }
    printf("buf = %s\n", buf);


    return 0;
}
