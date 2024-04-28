/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月22日 星期一 22时34分55秒
 ************************************************************************/

#include<stdio.h>

int main(int argc, char **argv) {
    int i = 0;
    for (i; i < argc; i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }
    return 0;
}
