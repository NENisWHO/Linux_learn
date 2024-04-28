/*************************************************************************
	> File Name: 4_alarm.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月24日 星期三 21时08分04秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<unistd.h>

//测试alarm函数
int main(void) {

    unsigned int ret = 0;

    //第一次设置闹钟 5秒后就超时 发送对应的信号
    ret = alarm(5);

    printf("上一次闹钟剩下的时间是 %u\n", ret);

    sleep(2);
    //之前没有超时的闹钟被新的设置给覆盖了
    ret = alarm(4);
    printf("上一次闹钟剩下的时间是 %u\n", ret);
    
    printf("按下任意建继续...\n");
    getchar();

    return 0;
}
