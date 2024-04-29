/*************************************************************************
	> File Name: 2_ntohl.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月27日 星期六 15时29分31秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>

//网络转主机
int main(int arg, char *argv[]) {
    
    unsigned char buf[4] = {1, 1, 168, 192};
    unsigned int num = *(int *)buf;
    unsigned int sum = ntohl(num);
    unsigned char *p = (unsigned char *)&sum;
    printf("%d %d %d %d\n", *p, *(p+1), *(p+2), *(p+3));
    
    return 0;
}
