/*************************************************************************
	> File Name: 8_printer.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月25日 星期四 21时05分08秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

void* fun1(void * arg) {
    int i = 0;
    for (i = 'A'; i <= 'Z'; i++) {
        putchar(i);
        fflush(stdout);
        usleep(100000); //100ms
    }
    return NULL;
}

void* fun2(void * arg) {
    int i = 0;
    for (i = 'a'; i <= 'z'; i++) {
        putchar(i);
        fflush(stdout);
        usleep(100000); //100ms
    }
    return NULL;
}



//模拟输出字符
int main(void) {
    
    pthread_t tid1, tid2;

    //创建两个线程
    pthread_create(&tid1, NULL, fun1, NULL);
    pthread_create(&tid2, NULL, fun2, NULL);

    //等待两个线程结束
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    
    printf("\n");
    printf("main thread exit...\n");

    return 0;
}
