/*************************************************************************
	> File Name: 7_pthread_join.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月25日 星期四 20时55分05秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<pthread.h>
#include<unistd.h>

void *fun(void *arg) {

    int i = 0;
    for (i = 0; i < 5; i++) {
        printf("fun thread do working %d\n", i);
        sleep(1);
    }
    return (void*)0x3;
}

//回收线程的资源
int main(void) {
    
    int ret = -1;
    void *retp = NULL;
    pthread_t tid = -1;

    //创建线程
    ret = pthread_create(&tid, NULL, fun,NULL);
    if (0 != ret) {
        printf("pthread_creat failed...\n");
        return 1;
    }
    printf("main thread running...\n");
    //等待线程结束
    ret = pthread_join(tid, &retp);
    if (0 != ret) {
        printf("pthread_join failed...\n");
        return 1;
    }
    
    printf("retp: %p\n", retp);
    printf("main thread exit...\n");

    return 0;
}
