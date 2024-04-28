/*************************************************************************
	> File Name: 8_opendir.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月20日 星期六 15时58分07秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<dirent.h>

int main(void) {

    DIR* dir = NULL;
    struct dirent* d = NULL;

    //1.打开目录
    dir = opendir("/home/learn/linux_system/04_file");
    if(NULL == dir) {
        perror("opendir");
        return 1;
    }
    printf("打开目录成功......\n");

    //2.循环读取目录内容
    while(1) {
        //读取目录的内容
        d = readdir(dir);
        if(NULL == d) {
            //perror("readdir");
            break;
        }
        //printf("d_type:%hu d_name:%s\n", d->d_type, d->d_name);
        if(d->d_type == DT_REG) {
            printf("d_type: 普通文件, d_name:%s\n", d->d_name);
        }else if(d->d_type == DT_DIR) {
            printf("d_type: 目录文件, d_name:%s\n", d->d_name);
        }
    }

    //3.关闭目录
    closedir(dir);


    return 0;
}
