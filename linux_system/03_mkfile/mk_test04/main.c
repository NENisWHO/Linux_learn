/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月18日 星期四 14时51分03秒
 ************************************************************************/

#include<stdio.h>
#include"add.h"
#include"sub.h"
#include"mul.h"
#include"div.h"

int main() {
    int a = 6;
    int b = 3;
    printf("x + y = %d\n", add(a, b));
    printf("x - y = %d\n", sub(a, b));
    printf("x * y = %d\n", mul(a, b));
    printf("x / y = %d\n", div(a, b));
    printf("hello \n");
    return 0;
}
