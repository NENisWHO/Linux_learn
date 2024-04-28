/*************************************************************************
	> File Name: 1_getsid.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月25日 星期四 16时09分30秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<unistd.h>

//测试setsid和getsid
int main(void) {
    pid_t pid = -1;

    //getsid 获取当前进程组会话ID
    pid = getsid(0);
    if (-1 == pid) {
        perror("getsid");
        return 1;
    }
    printf("sid: %d\n", pid);
    
    //暂停一下 , ps -ajx | grep a.out 查看一下三个id号
    getchar();
    //setsid 新建一个会话；进程组组长不能创建新会话
    pid = setsid();
    if (-1 == pid) {
        perror("setsid");
        return 1;
    }
    printf("sid: %d\n", pid);

    return 0;
}
