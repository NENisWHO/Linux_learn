/*************************************************************************
	> File Name: 5_pthread_self.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月25日 星期四 19时43分28秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<pthread.h>

//gcc 5_*.c -pthread 指定链接线程库

//线程常用函数
int main(void) {
    
    pthread_t tid = -1;

    //获取当前线程的线程号
    tid = pthread_self();
    printf("tid : %lu\n", tid);


    //比较两个线程ID是否相等
    //if (tid1 == tid2) 不可以
    if (pthread_equal(tid, pthread_self())) {
        printf("两个线程ID相同..\n");
    }else {
        printf("两个线程ID不相同..\n");
    }

    return 0;
}
