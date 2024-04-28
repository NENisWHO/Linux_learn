/*************************************************************************
	> File Name: 2_stat.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月19日 星期五 19时40分14秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

//显示文件类型的第一个版本
int show_file_type(struct stat *s) {
    switch(s->st_mode & S_IFMT) {
        //普通文件
        case S_IFREG:
            printf("该文件是普通文件\n");
            break;
         //目录
        case S_IFDIR:
            printf("该文件是目录\n");
            break;
        //字符设备
        case S_IFCHR:
            printf("该文件是字符设备\n");
            break;
        //块设备
        case S_IFBLK:
            printf("该文件是块设备\n");
            break;
        //套接字
        case S_IFSOCK:
            printf("该文件是套接字\n");
            break;
        //管道
        case S_IFIFO:
            printf("该文件是管道\n");
            break;
        //符号连接
        case S_IFLNK:
            printf("该文件是符号链接\n");
            break;
        default:
            printf("未知文件类型\n");
    }
    return 0;
}

int show_file_type_v2(struct stat* s) {
   //普通文件
    if(S_ISREG(s->st_mode)) {
        printf("Is a regular file\n");
    }
   //目录
    if(S_ISDIR(s->st_mode)) {
        printf("Is a directory\n");
    }
   //字符设备
    if(S_ISCHR(s->st_mode)) {
        printf("Is a character special file\n");
    }
   //块设备
    if(S_ISBLK(s->st_mode)) {
        printf("Is a block special file\n");
    }
   //管道文件
    if(S_ISFIFO(s->st_mode)) {
        printf("Is a pipe or FIFO\n");
    }
   //符号连接
    if(S_ISLNK(s->st_mode)) {
        printf("Is a symbolic link\n");
    }
   //套接字
    if(S_ISSOCK(s->st_mode)) {
        printf("Is a socket\n");
    }
}


int show_permission(struct stat* s) {
//拥有者权限
    //拥有着读权限
    if (s->st_mode & S_IRUSR) {
        printf("r");
    }else{
        printf("-");
    }
    //拥有着写权限
    if (s->st_mode & S_IWUSR) {
        printf("w");
    }else{
        printf("-");
    }
    //拥有着执行权限
    if (s->st_mode & S_IXUSR) {
        printf("x");
    }else{
        printf("-");
    }
//所属组    
    //读权限
    if (s->st_mode & S_IRGRP) {
        printf("r");
    }else{
        printf("-");
    }
    //写权限
    if (s->st_mode & S_IWGRP) {
        printf("w");
    }else{
        printf("-");
    }
    //执行权限
    if (s->st_mode & S_IXGRP) {
        printf("x");
    }else{
        printf("-");
    }
//其他人
    //读
    if (s->st_mode & S_IROTH) {
        printf("r");
    }else{
        printf("-");
    }
    //写权限
    if (s->st_mode & S_IWOTH) {
        printf("w");
    }else{
        printf("-");
    }
    //执行
    if (s->st_mode & S_IXOTH) {
        printf("x");
    }else{
        printf("-");
    }
    printf("\n");
    return 0;
}

//获取文件的类型和存储权限
int main(int argc, char** argv) {
    
    int ret = -1;
    struct stat s;

    //容错判断。
    if(2 != argc) {
        printf("usage: ./a.out filename\n");
        return 1;
    }
    
    //获取文件信息, argv[0] 是 a.out; argv[1] 是 filename
    ret = stat(argv[1], &s);
    if(ret == -1) {
        perror("stat");
        return 1;
    }

    //显示文件类型
    show_file_type(&s);
    show_file_type_v2(&s);
    show_permission(&s);

    return 0;
}
