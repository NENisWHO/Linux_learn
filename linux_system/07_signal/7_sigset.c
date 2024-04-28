/*************************************************************************
	> File Name: 7_sigset.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月24日 星期三 22时03分49秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>

void show_set(sigset_t *s) {
    int i = 0;
    for (i = 1; i < 32; i++) {
        if (sigismember(s, i)) {
            printf("1");
        }else {
            printf("0");
        }
    }
    putchar('\n');
}

//信号集处理函数
int main(void) {

    int i = 0;

    //信号集集合
    sigset_t set;

    //清空集合
    sigemptyset(&set);
    show_set(&set);
    //将所有信号加入到set集合中
    sigfillset(&set);
    show_set(&set);
   
    //将信号2和3从信号集中移除
    sigdelset(&set, SIGINT);
    sigdelset(&set, SIGQUIT);
    show_set(&set);

    //将信号2加到集合中
    sigaddset(&set, SIGINT);
    show_set(&set);

    return 0;
}
