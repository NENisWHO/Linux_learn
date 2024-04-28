/*************************************************************************
	> File Name: 10_sigaction.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月24日 星期三 22时57分22秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>

//信号处理函数
void fun(int signo) {
    printf("捕捉到信号 %d\n", signo);
}

//新的信号处理函数
void fun1(int signo, siginfo_t *info, void *context) {
    printf("捕捉到信号 %d\n", signo);
}

//演示sigaction函数使用
int main(void) {
    int ret = -1;
#if 0
    struct sigaction act;
    //使用旧的信号处理函数指针
    act.sa_handler = fun;
    //标志为默认 默认使用旧的信号处理函数指针
    act.sa_flags = 0;
#else
    struct sigaction act;
    //使用新的信号处理函数指针
    act.sa_sigaction = fun1;
    //标志指定使用新的信号处理函数指针
    act.sa_flags = SA_SIGINFO;

#endif
    //信号注册
    ret = sigaction(SIGINT, &act, NULL);
    if(-1 == ret) {
        perror("sigaction");
        return 1;
    }   

    printf("按下任意建退出...\n");
    //getchar();
    //getchar();
    while(1) {
        getchar();
    }

    return 0;
}
