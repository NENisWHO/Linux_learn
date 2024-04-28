/*************************************************************************
	> File Name: 03_write.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月19日 星期五 15时29分48秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>

#define SIZE 128

int main(void) {
    
    int fd = -1;
    int ret = -1;
    char buff[SIZE];
    //1.以只读的方式打开文件
    fd = open("txt2", O_RDONLY, 0644);
    if(-1 == fd) {
        perror("open");
        return 1;
    }
    printf("fd = %d\n", fd);
    //2.读文件
    memset(buff, 0, SIZE);
    //从文件描述符fd中最多读取SIZE个字节保存到buff中，实际读取字节数通过返回值返回
    ret = read(fd, buff, SIZE);
    if(-1 == ret) {
        perror("read");
        return -1;
    }
    printf("write len: %d %s\n", ret, buff);

    printf("\n");
    //3.关闭文件
    close(fd);
    
    return 0;
}

