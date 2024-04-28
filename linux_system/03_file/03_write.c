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

int main(void) {
    
    int fd = -1;
    int ret = -1;
    char* str = "hello iscast";
    //1.以只写的方式打开文件
    fd = open("txt2", O_WRONLY | O_CREAT, 0644);
    if(-1 == fd) {
        perror("open");
        return 1;
    }
    printf("fd = %d\n", fd);
    //2.写文件
    ret = write(fd, str, strlen(str));
    if(-1 == ret) {
        perror("write");
        return -1;
    }
    printf("write len: %d\n", ret);

    printf("\n");
    //3.关闭文件
    close(fd);
    
    return 0;
}

