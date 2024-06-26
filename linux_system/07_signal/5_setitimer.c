/*************************************************************************
	> File Name: 5_setitimer.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月24日 星期三 21时19分14秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<sys/time.h>
#include<signal.h>

//信号处理函数
void fun(int signo) {
    printf("捕捉到信号：%d\n", signo);
}


int main(void) {

    int ret = -1;
    
    struct itimerval tmo;

    //第一次触发时间
    tmo.it_value.tv_sec = 3;
    tmo.it_value.tv_usec = 0;

    //触发周期
    tmo.it_interval.tv_sec = 2;
    tmo.it_interval.tv_usec = 0;

    //捕捉信号 SIGALRM
    signal(SIGALRM, fun);

    //设置定时器
    ret = setitimer(ITIMER_REAL, &tmo, NULL);
    if(-1 == ret) {
        perror("setitimer");
        return 1;
    }

    //进程收到闹钟超时信号之后就会终止该进程
    printf("按下任意建继续...\n");
    getchar();

    return 0;
}

