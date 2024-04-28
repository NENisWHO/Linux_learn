/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月18日 星期四 15时57分04秒
 ************************************************************************/

#include<stdio.h>

void func(void) {
    for(int i = 0; i < 10; i++) {
        printf("func==> i = %d\n", i);
    }
}

int main(int argc, char **argv) {
    
    int a = 10;
    for (int i = 0; i < a; i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }
    
    func();
    printf("hellp itcast\n");

    return 0;
}
