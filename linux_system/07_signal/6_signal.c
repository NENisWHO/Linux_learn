/*************************************************************************
	> File Name: 6_signal.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月24日 星期三 21时35分35秒
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
    int pid = getpid();
    printf("pid: %d\n", pid);
    //Ctrl + c
    signal(SIGINT, func1);

    //Ctrl + '\'
    signal(SIGQUIT, func2);

    while(1) {
        sleep(1);   
    }

    return 0;
}
