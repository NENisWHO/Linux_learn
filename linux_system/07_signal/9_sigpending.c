/*************************************************************************
	> File Name: 9_sigpending.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月24日 星期三 22时35分01秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

//信号处理函数1
void func1(int signum) {
    printf("捕捉信号：%d\n", signum);
}

//信号处理函数2
void func2(int signum) {
    printf("捕捉信号：%d\n", signum);
}

//信号注册函数
int main(void) {
    
    sigset_t set;
    sigset_t oldset;
    int ret = 0;

    int pid = getpid();
    printf("pid: %d\n", pid);
    //Ctrl + c
    signal(SIGINT, func1);

    //Ctrl + '\'
    signal(SIGQUIT, func2);
    
    printf("按下回车键 阻塞信号2\n");
    getchar();
    
    sigemptyset(&oldset);
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGQUIT);


    //设置屏蔽编号为2和3的信号
    ret = sigprocmask(SIG_BLOCK, &set, &oldset);
    if (-1 == ret) {
        perror("sigprocmask");
        return 1;
    }
    printf("设置屏蔽编号为2的信号成功...\n");
//////////////////////////////////
    printf("按下回车键获取未决的信号\n");
    getchar();

    //获取未决的信号集
    sigemptyset(&set);
    ret = sigpending(&set);
    if (-1 == ret) {
        perror("sigpending");
        return 1;
    }
    //
    int i = 0;
    printf("处于未决的信号有：");
    for (i = 0; i < 32; i++) {
        if (sigismember(&set, i)) {
            printf("%d", i);
        }
    }
    putchar('\n');
///////////////////////////////////
    printf("按下回车键解除编号为2的信号的阻塞...\n");
    getchar();

    //将信号屏蔽集设置为原来的集合
    ret = sigprocmask(SIG_SETMASK, &oldset, NULL);
    if (-1 == ret) {
        perror("sigprocmask");
        return 1;
    }

    printf("按下回车键退出...\n");
    getchar();

    return 0;
}
