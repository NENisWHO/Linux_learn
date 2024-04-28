/*************************************************************************
	> File Name: 5_exit.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月21日 星期日 15时47分06秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

int main(void) {

    printf("hello world");

    //直接退出，不做任何事后清理工作
    //_exit(0); 等价于_Exit(0)
    _Exit(0);
    //相当于return 0；
    //exit(0);
    //return 0;
}
