/*************************************************************************
	> File Name: 1_ttyname.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月25日 星期四 15时54分40秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<unistd.h>

int main(void) {

    
    printf("fd 0: %s\n", ttyname(0));
    printf("fd 1: %s\n", ttyname(1));
    printf("fd 2: %s\n", ttyname(2));
    

    return 0;
}
