/*************************************************************************
	> File Name: 6_pthread_creat.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月25日 星期四 19时56分15秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<pthread.h>

void *fun(void* arg) {
    printf("新的线程执行任务 tid: %lu\n", pthread_self());

    return  NULL;
}

void *fun1(void* arg) {
    int var = (int)(long)arg; 
    //指针（8字节）转为int（4字节），先转为long
    printf("线程2 var = %d\n", var);
    return NULL;
}

//创建线程
int main(void) {

    int ret = -1;
    pthread_t tid = -1;
    pthread_t tid2 = -1;

    //创建一个线程
    ret = pthread_create(&tid, NULL, fun, NULL);
    if( 0 != ret) {
        printf("pthread_create failed...\n");
        return 1;
    }
    
    //创建一个线程
    ret = pthread_create(&tid2, NULL, fun1, (void*)0x3);
    if( 0 != ret) {
        printf("pthread_create failed...\n");
        return 1;
    }
    //
    printf("main thread...tid:%lu\n", pthread_self());

    printf("按下任意建主线程退出...\n");
    getchar();

    return 0;
}
