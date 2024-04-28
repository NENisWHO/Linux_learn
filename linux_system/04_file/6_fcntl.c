/*************************************************************************
	> File Name: 5_fcntl.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月20日 星期六 15时00分46秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>


//fcntl 设置和获取文件状态标记
int main(void) {

    int fd = -1;
    int ret = -1;

    //1打开文件
    fd = open("txtfcntl", O_RDWR | O_CREAT, 0644);
    if(-1 == fd) {
        perror("open");
        return 1;
    }
    //2.获取文件状态标记
    ret = fcntl(fd, F_GETFL);
    if(-1 == ret) {
        perror("fcntl");
        return 1;
    }

    if(ret & O_APPEND) { //位于判断
        printf("before append\n");
    }else {
        printf("before not append\n");
    }
    //3.设置文件状态标记
    ret = ret | O_APPEND; //位或追加
    ret = fcntl(fd, F_SETFL, ret);
    if(-1 == ret) {
        perror("fcntl");
        return 1;
    }
    
    //4.获取文件状态标记
    ret = fcntl(fd, F_GETFL);
    if(-1 == ret) {
        perror("fcntl");
        return 1;
    }

    if(ret & O_APPEND) {
        printf("after append\n");
    }else {
        printf("after not append\n");
    }
    //5.关闭文件
    close(fd);
    return 0;
}
