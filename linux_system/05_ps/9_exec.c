/*************************************************************************
	> File Name: 9_exec.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月21日 星期日 19时42分33秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(void) {
    
    printf("hello itcast\n");

    //arg0, arg1, arg2, arg3, ... argn
    //arg0一般是可执行文件名 argn必须是NULL
    //等价于执行ls -l /home
    //execlp("ls", "ls", "-l", "/home", NULL);
   
    //execl("ls", "ls", "-l", "/home", NULL);
    //第一个参数是可执行文件的绝对路径或者相对路径
    //第二个参数一般是可执行文件的名字
    //中间的参数是可执行文件的参数
    //最后一个参数是NULL
    execl("/bin/ls", "ls", "-l", "/home", NULL);


    //这一行不会被执行，因为exec**-进程替换了；进程替换失败才执行
    printf("hello world\n");
    return 0;
}
