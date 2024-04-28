/*************************************************************************
	> File Name: 4_dup.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月20日 星期六 14时39分19秒
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

    //打开文件
    fd = open("txtdup", O_RDWR | O_CREAT, 0644);
    if( -1 == fd ) {
        perror("open");
        return 1;
    }

    //文件描述符复制
    newfd = 2;
    //如果文件描述符2已经跟某个文件关联了，那么就先解除与该文件的关联，然后将该文件描述符与fd关联同一个文件
    //newfd = dup(fd);
    dup2(fd, newfd);
    if( -1 == newfd ) {
        perror("dup");
        return 1;
    }
    //操作
    write(fd, "ABCDEFG", 7);
    write(newfd, "1234567", 7);
    //关闭文件描述符
    close(fd);
    close(newfd);
    return 0;
}
