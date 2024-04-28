/*************************************************************************
	> File Name: 3_deallock.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月26日 星期五 14时30分07秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

//线程互斥量变量
pthread_mutex_t mutex1;
pthread_mutex_t mutex2;

//fun1
void* fun1(void* arg) {
    //线程1先申请资源1 再申请资源2
    pthread_mutex_lock(&mutex1);
    printf("线程1加锁资源1 ok...\n");
    pthread_mutex_lock(&mutex2);
    printf("线程1加锁资源2 ok...\n");

    printf("线程1执行临界区代码...\n");
    //解锁
    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);
    return NULL;
}

void* fun2(void* arg) {
    //线程2先申请资源2 再申请资源1
    pthread_mutex_lock(&mutex2);
    printf("线程2加锁资源2 ok...\n");
    pthread_mutex_lock(&mutex1);
    printf("线程2加锁资源1 ok...\n");

    printf("线程2执行临界区代码...\n");
    //解锁
    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);
    return NULL;
}

int main(void) {
    
    int ret = -1;
    pthread_t tid1, tid2;

    //初始化互斥量
    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&mutex2, NULL);


    //创建两个线程
    pthread_create(&tid1, NULL, fun1, NULL);
    pthread_create(&tid2, NULL, fun2, NULL);

    //回收线程资源
    ret = pthread_join(tid1, NULL);
    if (0 != ret) {
        printf("pthread_join failed...\n");
        return 1; 
    }
    ret = pthread_join(tid2, NULL);
    if (0 != ret) {
        printf("pthread_join failed...\n");
        return 1; 
    }

    //销毁
    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);

    return 0;
}
