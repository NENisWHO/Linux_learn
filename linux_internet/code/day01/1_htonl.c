/*************************************************************************
	> File Name: 01_htonl.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月27日 星期六 15时06分07秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>

int main(int argc, char *argv[]) {
    
    char buf[4] = {192, 168, 1, 2}; //四个字节，32位
    int num = *(int *)buf; //将数组转为指针解出数据
    
    printf("num: %d\n", num);
    int sum = htonl(num);
    printf("sum: %d\n", sum);
    unsigned char *p= &sum;
    
    printf("%d %d %d %d\n", *p, *(p+1), *(p+2), *(p+3));
    
    unsigned short a = 0x0102;
    unsigned short b = htons(a);
    printf("%x\n", b);

    return 0;
}
