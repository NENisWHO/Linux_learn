/*************************************************************************
	> File Name: 3_abort.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月24日 星期三 20时58分32秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include<unistd.h>

int main(void) {

    int i = 1;

    while(1) {
        printf("do working %d\n", i);
        if(i == 4) {
            //给自己发送一个编号为6的信号 默认终止进程
            abort();    
        }

        i++;
        sleep(1);
    }

    return 0;
}
