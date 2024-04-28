/*************************************************************************
	> File Name: 7_producer_cond.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月26日 星期五 17时38分53秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
#include<unistd.h>


//链表节点
typedef struct _node_t {
    int data;
    struct _node_t *next;
}node_t;

node_t *head = NULL;

//条件变量
pthread_cond_t cond;
//互斥变量
pthread_mutex_t mutex;

//生产者线程
void* producer(void* arg) {
    //循环生产产品
    while(1) {
        //加锁
        pthread_mutex_lock(&mutex);
        //分配节点空间
        node_t *new = malloc(sizeof(node_t));
        if(NULL == new) {
            printf("malloc failed...\n");
            break;
        }
        memset(new, 0, sizeof(node_t));
        new->data = random() % 100 + 1;
        new->next = NULL;
        printf("生产者生产%d\n", new->data);

        //头插法
        new->next = head;
        head = new;

        //解锁
        pthread_mutex_unlock(&mutex);
        //唤醒因为条件变量而阻塞的线程
        pthread_cond_signal(&cond);
        //随机睡眠
        sleep(random() %3 +1);
    }

    return NULL;
}
//消费者线程
void* customer(void* arg) {
    
    node_t *tmp = NULL;
    //循环消费
    while(1) {
        //加锁
        pthread_mutex_lock(&mutex);
    
        if(NULL == head) {
            //等待。。。
            printf("产品连表为空...先休息两秒钟...\n");
            //如果连表为空 就阻塞
            pthread_cond_wait(&cond, &mutex);
        }
        //删除第一个节点
        tmp = head;
        head = head->next;
        printf("消费者消费%d\n", tmp->data);
        free(tmp);
        //解锁
        pthread_mutex_unlock(&mutex);

        sleep(random() %3 +1);

    }
    return NULL;
}

//生产者和消费者模型 条件变量的模型
int main(void) {
    srandom(getpid());
    int ret = -1;
    pthread_t tid1, tid2;
    //初始化条件变量
    ret = pthread_cond_init(&cond, NULL);
    if(0 != ret) {
        printf("pthread_cond_init failed...\n");
        return 1;
    } 
    //初始化互斥量  
    ret = pthread_mutex_init(&mutex, NULL);
    if(0 != ret) {
        printf("pthread_mutex_init failed...\n");
        return 1;
    } 
    //创建两个线程
    //一个生产者
    pthread_create(&tid1, NULL, producer, NULL);
    //一个消费者
    pthread_create(&tid2, NULL, customer, NULL);

    //等待两个线程结束
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    
    //销毁
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);

    return 0;
}
