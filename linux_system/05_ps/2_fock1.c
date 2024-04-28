/*************************************************************************
	> File Name: 2.fock.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月21日 星期日 08时27分10秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

//创建一个子进程
int main(void) {
    
    printf("hello world\n");
    printf("getpid: %d\n", getpid());
    printf("getppid: %d\n", getppid());
    //创建子进程
    fork();
    int a = 1, b = 2;
    printf("a + b = %d\n", a + b);
    return 0;
}
