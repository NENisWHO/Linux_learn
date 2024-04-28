/*************************************************************************
> File Name: 6_pthread_cond_init.c
> Author: 
> Mail: 
> Created Time: 2024年04月26日 星期五 16时57分02秒
************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>

int flag = 0;

//互斥量
pthread_mutex_t mutex;

//条件变量
pthread_cond_t cond;

//改变条件的线程
void* fun1(void* arg) {

    while(1) {
        //加锁
        pthread_mutex_lock(&mutex);
        flag = 1;
        //解锁
        pthread_mutex_unlock(&mutex);

        //唤醒因为条而阻塞的线程
        pthread_cond_signal(&cond);
        //printf("")

        sleep(2);
    }

    return  NULL;   
}

//等待条件的线程
void* fun2(void* arg) {
    while(1) {
        //加锁
        pthread_mutex_lock(&mutex);

        if (0 == flag) {
            //等待条件满足 会阻塞
            pthread_cond_wait(&cond, &mutex);
        }
        printf("线程二因为条件满足 开始运行...\n");
        flag = 0;
        //解锁
        pthread_mutex_unlock(&mutex);
        sleep(2);
    }

    return NULL;
}


//条件变量的应用
int main(void) {

    int ret = -1;
    pthread_t tid1, tid2;
    ///  初始化条件变量
    ret = pthread_cond_init(&cond, NULL);
    if (0 != ret) {
        printf("pthread_cont_init failed...\n");
        return 1;
    }
    ///  初始化互斥量
    ret = pthread_mutex_init(&mutex, NULL);
    if (0 != ret) {
        printf("pthread_mutex_init failed...\n");
        return 1;
    }


    //创建两个线程
    pthread_create(&tid1, NULL, fun1, NULL);
    pthread_create(&tid2, NULL, fun2, NULL);



    //回收线程资源
    ret =  pthread_join(tid1, NULL);
    if (0 != ret) {
        printf("pthread_join failed...\n");
        return 1;
    }
    pthread_join(tid2, NULL);
    if (0 != ret) {
        printf("pthread_join failed...\n");
        return 1;
    }

    //销毁互斥量
    pthread_mutex_destroy(&mutex);
    //销毁条件变量
    pthread_cond_destroy(&cond);
    return 0;
}
