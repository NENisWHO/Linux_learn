/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月23日 星期二 21时29分06秒
 ************************************************************************/

#include<stdio.h>
#include<ctype.h>

int main() {

    int ch = getchar();
    while(ch != EOF) {
        putchar(toupper(ch));
        ch = getchar();
    }
        
    return 0;
}
