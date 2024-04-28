/*************************************************************************
	> File Name: 1_printer_mutex.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月26日 星期五 09时36分10秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

///互斥锁变量
pthread_mutex_t mutex;


void* fun1(void * arg) {
    
    int i = 0;
    /// 加锁
    pthread_mutex_lock(&mutex);

    for (i = 'A'; i <= 'Z'; i++) {
        putchar(i);
        fflush(stdout);
        usleep(100000); //100ms
    }
    /// 解锁
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void* fun2(void * arg) {

    int i = 0;
    /// 加锁
    pthread_mutex_lock(&mutex);
    ///////// 临界区代码
    for (i = 'a'; i <= 'z'; i++) {
        putchar(i);
        fflush(stdout);
        usleep(100000); //100ms
    }

    /// 解锁
    pthread_mutex_unlock(&mutex);
    return NULL;
}



//模拟输出字符
int main(void) {
    
    pthread_t tid1, tid2;
   int ret = -1; 
    /// 初始化一个互斥量 互斥锁
    ret = pthread_mutex_init(&mutex, NULL);
    if (0 != ret) {
        printf("pthread_mutex_init failed..\n");
        return 1;
    }
    printf("初始化一个互斥量成功...\n");

    //创建两个线程
    pthread_create(&tid1, NULL, fun1, NULL);
    pthread_create(&tid2, NULL, fun2, NULL);

    //等待两个线程结束
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    
    printf("\n");
    printf("main thread exit...\n");

    /// 销毁互斥量 互斥锁
    pthread_mutex_destroy(&mutex);

    return 0;
}
