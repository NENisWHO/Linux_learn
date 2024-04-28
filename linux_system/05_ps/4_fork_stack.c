/*************************************************************************
	> File Name: 4_fork_stack.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月21日 星期日 15时12分23秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

//valgrind ./a.out   查看内存泄漏

//全局变量在数据段中
int num = 100; 

//父子进程地址空间  读时共享，写时拷贝
int main(void) {
    //局部变量，在栈区
    int var = 88;
    pid_t pid = -1;
    int * p = NULL;
    
    //在堆区分配内存空间
    p = malloc(sizeof(int));
    if(p == NULL) {
        printf("malloc failed..\n");
        return 1;
    }
    memset(p, 0, sizeof(int));
    
    *p = 100;
    
    //创建子进程
    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 0;
    }else if (pid == 0) {
        sleep(1);
        printf("child after sleep var = %d, num = %d, *p = %d\n", var, num, *p);
        free(p);
        p = NULL;
    }else if (pid > 0) {
        printf("father var = %d, num = %d, *p = %d\n", var, num, *p);
        var++;
        num++;
        (*p)++;
        printf("father ++ var = %d, num = %d, *p = %d\n", var, num, *p);
    free(p);
    p = NULL;
    }
     
    return 0;
}
