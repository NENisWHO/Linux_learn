/*************************************************************************
	> File Name: 1_pipe.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月22日 星期一 08时13分29秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include<unistd.h>
//用于创建无名管道
int main(void) {
    int pfd[2];
    int ret = -1;
    
    //创建一个无名管道
    ret = pipe(pfd);
    if (ret == -1) {
        perror("pipe");
        return 1;
    }
    
    //pfd[0]用于读  pfd[1]用于写
    printf("pfd[0]:%d pfd[1]:%d \n", pfd[0], pfd[1]);
    
    //查看管道缓冲区的大小
    printf("pipe size: %ld\n", fpathconf(pfd[0], _PC_PIPE_BUF));
    printf("pipe size: %ld\n", fpathconf(pfd[1], _PC_PIPE_BUF));

    printf("pc name max: %ld\n", fpathconf(pfd[0], _PC_NAME_MAX));

    //关闭文件
    close(pfd[0]);
    close(pfd[1]);

    return 0;
}
