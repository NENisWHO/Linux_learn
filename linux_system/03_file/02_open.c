/*************************************************************************
	> File Name: 02_open.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月19日 星期五 14时56分47秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main(void) {
    
    int fp = -1;

    //1.以只读的方式打开一个文件，如果文件不存在就报错
    //fp = open("txt", O_RDONLY);
    //2.以只写的方式打开一个文件，如果文件存在就直接打开，如果文件不存在就新建一个文件
    //fp = open("txt1", O_WRONLY | O_CREAT, 0644);
    
    //3.以只写的方式打开一个文件，如果文件存在就报错，如果文件不存在就新建一个
    //fp = open("txt1", O_WRONLY | O_CREAT | O_EXCL, 0644);
    
    //4.以读写的方式打开一个文件，如果文件存在就打开，如果文件不存在就新建一个文件
    //fp = open("txt1", O_RDWR | O_CREAT, 0644);
    
    //5.如果文件不存在就新建一个文件，如果文件存在打开后清空
    //fp = open("txt1", O_WRONLY | O_TRUNC | O_CREAT, 0644);
    
    //6.以只写的方式和追加的方式打开一个文件，如果文件不存在会报错
    fp = open("txt1", O_WRONLY | O_APPEND);
    if( -1 == fp ) {

        perror("open");
        
        return 1;
    }

    //文件描述符
    printf("fp = %d\n", fp);

    //关闭文件
    close(fp);
    return 0;
} 
