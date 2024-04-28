/*************************************************************************
	> File Name: 5_fcntl.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月20日 星期六 15时00分46秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main(void) {

    int fd = -1;
    int newfd = -1;
    int ret = -1;

    //打开文件
    fd = open("txtfcntl", O_RDWR | O_CREAT, 0644);
    if(-1 == fd) {
        perror("open");
        return 1;
    }
    printf("fd = %d\n", fd);
    //文件描述符复制
    //等价于dup函数
    //第三个参数0, 表示返回一个最小的可用的文件描述符，并且大于等于0
    newfd = fcntl(fd, F_DUPFD, 0);
    if(-1 == newfd) {
        perror("fcntl");
        return 1;
    }
    printf("newfd = %d\n", newfd);
    
    //写文件
    write(fd, "123456789", 9);
    write(newfd, "abcdefgh", 9);

    //关闭文件
    close(fd);
    close(newfd);
    return 0;
}
