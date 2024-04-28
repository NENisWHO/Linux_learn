/*************************************************************************
	> File Name: 11_mmap_anonymous.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月22日 星期一 16时27分10秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<sys/wait.h>
#include<error.h>
#include<fcntl.h>
#include<unistd.h>

//父子进程使用匿名映射进行进程间通信
int main(void) {
    
    int ret = -1;
    void* addr = NULL;
    pid_t pid = -1;
    
    //1.创建匿名映射
    addr = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (MAP_FAILED == addr) {
        perror("mmap");
        return 1;
    }
    //2.创建子进程
    pid = fork();
    if (pid == -1) {
        perror("fork");
        munmap(addr, 4096);
        return 1;
    }
    //3.父子进程通信
    if (0 == pid) {
        //zi write
        memcpy(addr, "1234567890", 10);
    }else {
        //fu read
        wait(NULL);
        printf("parent process: %s\n",(char *)addr);
    }

    //4.断开映射
    munmap(addr, 4096);

    return 0;
} 
