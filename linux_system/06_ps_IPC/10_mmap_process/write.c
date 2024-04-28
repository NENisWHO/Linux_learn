/*************************************************************************
	> File Name: 9_mmap_fork.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月22日 星期一 15时40分23秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<sys/wait.h>

//父子进程使用存储映通信
int main(void) {
    
    int fd = -1;
    int ret = -1;
    pid_t pid = -1;
    void* addr = NULL;

    //1.以读写方式打开-个文件
    fd = open("txt", O_RDWR);
    if (-1 == fd) {
        perror("open");
        return 1;
    }

    //2.将文件映射到内存
    addr = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if(addr == MAP_FAILED) {
        perror("mmap");
        return 1;
    }
    printf("文件存储映射ok...\n");
    //3.关闭文件
    close(fd);

    //4.写存储映射区
    memcpy(addr, "1234567890", 10);

    //5.断开存储映射
    munmap(addr, 1024);

    return 0;
}
