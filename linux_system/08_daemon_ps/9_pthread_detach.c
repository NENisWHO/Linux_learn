/*************************************************************************
	> File Name: 9_pthread_detach.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月25日 星期四 21时17分36秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

void *fun(void* arg) {
    
    int i = 0;

    for (i = 0; i < 5; i++) {
        printf("pthread do working... %d\n", i);
        sleep(1);
    }

    return  NULL;
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
    
    //
    printf("main thread...tid:%lu\n", pthread_self());
    
    //设置线程分离
    ret = pthread_detach(tid);
    if(0 != ret) {
        printf("pthread_detach failed...\n");
        return 1;
    }
   
    //测试分离状态的线程是否可以被join
    ret = pthread_join(tid, NULL);
    if (0 != ret) {
        printf("pthread_join failed...\n");
    }else {
        printf("join ok\n");
    }


    printf("按下任意建主线程退出...\n");
    getchar();

    return 0;
}
