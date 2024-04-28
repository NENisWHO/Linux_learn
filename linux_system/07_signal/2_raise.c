/*************************************************************************
	> File Name: 2_raise.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月24日 星期三 20时52分10秒
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

//自己给自己一个信号
int main(void) {
    int i = 1;

    while(1) {
        printf("do working %d\n", i);
        
        //自己给自己一个信号
        if(i == 4) {
            //自己给自己一个编号15的信号
            kill(getpid(), SIGTERM);
            //raise(SIGTERM);
        }
        i++;
        sleep(1);
    }
    
    return 0;
}
