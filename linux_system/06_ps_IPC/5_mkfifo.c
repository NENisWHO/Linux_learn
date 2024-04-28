/*************************************************************************
	> File Name: 5_mkfifo.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月22日 星期一 14时08分41秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>


//通过mkfifo函数创建一个管道文件
int main(void) {

    int ret = -1;

    ret = mkfifo("fifo", 0644);
    if( -1 == ret) {
        perror("mkfifo");
        return 1;
    }
    
    printf("创建一个有名管道ok...\n");
    
    return 0;
}
