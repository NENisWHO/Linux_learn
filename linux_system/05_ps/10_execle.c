/*************************************************************************
	> File Name: 9_exec.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月21日 星期日 19时42分33秒
 ************************************************************************/

#define _GNU_SOURCE  //在unistd.h的前面才可以使用execvpe
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
   

//execvpe
//进程替换
int main(void) {

    char *argvs[] = {"ls", "-l", "/home", NULL};
    char *envp[] = {"ADDR=BEIJING", NULL};

    printf("hello itcast\n");

    //第一个参数是可执文件
    //第二个参数是指针:数组，最后一个一定以NULL结束
    //execvp("ls", argvs);

    //第一个参数是可执行文件的路径
    //第二个参数是指针数组，最后一个一定以NULL结束
    //execv("/bin/ls", argvs);


    //第一个参数是可执行文件的路径
    //最后一个参数是环境变量指针数组
    //execle("/bin/ls", "ls", "-l", "/home", NULL, envp);


    //第一个参数是可执行文件的路径
    //第二个参数是参数列表 指针数组
    //第三个参数是环境变量列表 指针数组
    execvpe("ls", argvs, envp);

    printf("hello world\n");
    return 0;
}
