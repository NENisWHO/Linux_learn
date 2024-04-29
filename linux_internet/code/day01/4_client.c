/*************************************************************************
	> File Name: 4_client.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月27日 星期六 16时13分55秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(int argc, char* argv[]) {
    
    //创建套接字
    int sock_fd;
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    //连接服务器
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    inet_pton(AF_INET,"192.168.93.1", &addr.sin_addr.s_addr);
    connect(sock_fd,(struct sockaddr *)&addr, sizeof(addr));
    //读写数据
    char buf[1024] = "";
    while(1) {
        int n = read(STDIN_FILENO, buf, sizeof(buf));
        write(sock_fd, buf, n);//发送数据给服务器
    }
    //关闭
    close(sock_fd);
    return 0;
}
