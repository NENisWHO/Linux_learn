# Docker

## 1. Docker拉取的镜像
```
docker pull 的镜像存放在
/var/lib/docker/image/ 目录下
```
## 2. Docker 的数据持久化
```
需求：
    1. 由镜像开启的容器，容器中的数据是在内存里的，
       在容器中安装的应用stop容器是不会消失的，重新run后还在；
       要是rm容器了，那么下载的应用也消失了。
    2. 那么就要求在rm容器后，应用还在。
解决：
    Docker的数据持久化：
    1）将本地目录映射到容器里
        mkdir -p /data/
        docker run -tid -v /data/:/data ubuntu bash ## -v 用来指定挂载目录 :前面的/data/为宿主机本地目录 :后面的/data/为容器里的目录，会在容器中自动创建
        
        测试：可以在/data/里创建一个文件echo "hello" > /data/1.txt；然后到容器里查看
             docker exec -it c82a5a00ae68 bash -c "cat /data/1.txt"
             
    2）数据卷
       创建数据卷：docker volume create testvol ##testvol为数据卷名字
       列出数据卷：docker volume ls
       查看数据卷信息：docker volume inspect testvol
       使用数据卷：docker run -itd --name aming01 -v testvol:/data/ ubuntu ##和前面直接映射本地目录不同,冒号左边为数据卷名字
       多个容器共享一个数据卷：docker run -itd --name aming02 -v testvol:/data/ ubuntu
       
    3）将宿主机上的文件快速传输进容器里
       docker cp /etc/fstab aming01:/tmp/test.txt
       docker exec -it aming01 cat /tmp/test.txt
```

## 3. run 和 start 
```
run：是由镜像启动容器，可以指定名字 
        -->"拉取镜像+启动容器"
docker run -itd redis
stop：是停掉up状态的容器 --> "停掉up的容器"
start：是拉起由stop而exited状态的容器 --> "拉起stop的容器"
```

## 4. 数据卷
```
删除数据卷：docker volume rm volumename ；这个卷得容器不使用才能删除

```

## 5. 针对Dockerfile中 RUN apt update 可能失败的问题解决方案
```
系统：rocky8
问题：Dockerfile中 RUN apt update 失败
      - 具体报错：ERROR: failed to solve: process "/bin/sh -c 
        apt update" did not complete successfully: exit code: 100
解决方案：
    解法：
    - 换清华源
        # 原本的 Dockerfile
        RUN apt-get update

        # 更改的 Dockerfile
        RUN sed -i "s@/archive.ubuntu.com/@/mirrors.tuna.tsinghua.edu.cn/@g" \
        /etc/apt/sources.list \
        && rm -Rf /var/lib/apt/lists/* \
        && apt-get update
    - 换网易源
        RUN sed -i "s@/archive.ubuntu.com/@/mirrors.163.com/@g" /etc/apt/sources.list \
        && rm -Rf /var/lib/apt/lists/* \
        && apt-get update
    - 终解
        RUN sed -i "s@/archive.ubuntu.com/@/mirrors.163.com/@g" /etc/apt/sources.list \
        && rm -rf /var/lib/apt/lists/* \
        && apt-get update --fix-missing -o Acquire::http::No-Cache=True

参考：[csdn](https://blog.csdn.net/weixin_43665662/article/details/117567941)
``` 

## 6. 
```
failed to register layer: open /usr/lib/mysqlsh/lib/python3.9/site-packages/oci/email/models/sender.py: no space left on device
```

## 7. 查看docker仓库
```
配置仓库
yum-config-manager \
 --add-repo \
 https://download.docker.com/linux/centos/docker-ce.repo
 
cat /etc/yum.repos.d/docker-ce.repo 
```

## 8.关闭防火墙
```
- 查看防火墙状态命令
    1）sudo systemctl status firewalld
    2) firewall-cmd --state
- 关闭防火墙命令
    1）临时性关闭（重启后失效）：sudo systemctl stop firewalld
    2) 永久性关闭（重启后生效）：sudo systemctl disable firewalld
- 开启防火墙命令
    1）临时性开启（重启后失效）：sudo systemctl start firewalld
    2) 永久性开启（重启后生效）：sudo systemctl enable firewalld
```

## 9.Docker中curl localhost失败
```
前提条件：
yum install nginx
yum install curl

失败提示：
root@84efe30d0963:/# curl localhost
curl: (7) Failed to connect to localhost port 80: Connection refused

解决：
/etc/init.d/nginx start

```

## 10.docker-compose 
```
1. 准备工作：
    1）安装docker-compose
    2）编辑wordpress的compose yaml文件  “将文件写在某个目录下比如：/data/docker”

2. 启动：docker-compose up -d
3. 查看：docker-compose ps “这个命令也要在上述目录/data/docker下执行才有结果”
4. 停止：docker-compose stop
```

## 11. 基础课12节-harbor，解决nginx一直处于restart状态
```
1. 在 sh install.sh 之后，先查看通过docker-compose ps
   查看容器，nginx一直处于restart状态
2. 通过docker logs nginx的id ；查看nginx的日志文件。
   找到问题是 “签证无法加载”
   具体显示
   2024/05/01 11:40:15 [emerg] 1#0: cannot load certificate "/etc/cert/server.crt": PEM_read_bio_X509_AUX() failed (SSL: error:0480006C:PEM routines::no start line:Expecting: TRUSTED CERTIFICATE)
nginx: [emerg] cannot load certificate "/etc/cert/server.crt": PEM_read_bio_X509_AUX() failed (SSL: error:0480006C:PEM routines::no start line:Expecting: TRUSTED CERTIFICATE)

    --》得出原因是因为老师给的签证可能过期了
3. 解决方案舍掉签证，使容器仅共个人使用；
   注释掉https及certificate和private_key

4. 在本机（非虚拟机）设置hosts即可
```

