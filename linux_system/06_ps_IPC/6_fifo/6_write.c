/*************************************************************************
	> File Name: 6_write.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月22日 星期一 14时16分46秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

#define SIZE 128

//只写大方式往管道写数据
int main(void) {
        
    int ret = -1;
    int fd = -1;
    char buf[SIZE];
    int i = 0;
    //1.只写的方式打开文件
    fd = open("fifo", O_WRONLY);
    if (-1 == fd) {
        perror("open");
        return 1;
    }
    printf("以只写的方式打开管道ok...\n");
    //2.写管道
    while (1) {
        memset(buf, 0, SIZE);
        sprintf(buf, "hello itcast %d", i++);
        ret = write(fd, buf, strlen(buf));
        if (ret <= 0) {
            perror("write");
            break;
        }
        printf("write fifo:%d\n", ret);
        sleep(1);
    }
    //3.关闭文件
    close(fd);
    return 0;
}
