/*************************************************************************
	> File Name: 3_inet_pton.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月27日 星期六 15时44分30秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>

//inet_pton 点分十进制转32位网络大段数据
int main(int argc, char* argv[]) {
    int ret = -1;    
    char buf[] ="192.168.1.4";
    unsigned int num = 0;
    ret = inet_pton(AF_INET, buf, &num);
    if (1 != ret) {
        perror("inet_pton");
        return 1;
    }
    unsigned char* p =(unsigned char*)&num;
    printf("%d %d %d %d\n", *p, *(p+1), *(p+2), *(p+3));

    char ip[16] = "";
    //inet_ntop(AF_INET, &num, ip, 16);
    printf("%s\n", inet_ntop(AF_INET, &num, ip, 16));

    return 0;
}
