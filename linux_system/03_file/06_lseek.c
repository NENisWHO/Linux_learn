/*************************************************************************
	> File Name: 06_lseek.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月19日 星期五 15时59分29秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<error.h>
#include<unistd.h>

#define SIZE 128

int main(void) {
        
    int fd = -1;
    int ret = -1;
    char buf[128];
    //打开文件
    fd = open("txt3", O_RDWR | O_CREAT, 0644);
    if (-1 == fd) {
        perror("open");
        return 1;
    }
    printf("fd = %d\n", fd);
    //lseek操作
    write(fd, "abcdefg", 7);
    //从文件开头偏移32个字节
    ret = lseek(fd, 32, SEEK_SET);
    if(-1 == ret) {
        perror("lseek");
        return 1;
    }
    write(fd, "1234567890", 10);

    //将文件位置指针指向文件开头
    lseek(fd, 0, SEEK_SET);
    memset(buf, 0, SIZE);
    ret = read(fd, buf, SIZE);
    printf("read ret %d | buf : %s\n", ret, buf);
    //关闭文件
    close(fd);
    return 0;
}
