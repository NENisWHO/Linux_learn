/*************************************************************************
	> File Name: errno.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月19日 星期五 10时31分03秒
 ************************************************************************/

#include<stdio.h>
#include<errno.h>
#include<string.h>

int main() {
    FILE *fp = fopen("txt", "r");
    if(NULL == fp) {
        printf("fopen faild...\n");
        printf("errno : %d\n", errno);  //打印错误码
        printf("fopen : %s\n", strerror(errno));//根据errno的值，解析出错原因
        //根据errno的值输出错误信息
        //提示字符串：出错原因
        perror("fopen");
        
        return 1;
    }

    return 0;
}
