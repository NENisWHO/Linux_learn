# 14_1 Linux podman容器技术与数据库基础

[toc]

---

>**数据库基础环境：CentOS7.9**
>**podman环境：rhel-8.2-x86_64-dvd.iso**

## 1. 源码编译安装

### 1.1 源码编译安装的步骤

* 步骤1：**安装开发工具gcc与make**，释放源代码至指定目录
* 步骤2：**tar解包**，释放源代码至指定目录
* 步骤3：**./configure 配置**，指定安装目录/功能模块等选项
* 步骤4：**make 编译**，生成可执行的二进制程序文件
* 步骤5：**make install 安装**，将编译好的文件复制到安装目录

### 1.2 源码编译安装的优点

* 获得软件的最新版，及时修复bug
* 软件功能可按需选择/定制，有更多软件可供选择
* 源码包适用各种平台

### 1.3 实例

```
1.安装开发工具
    [root@server ~]# yum -y install gcc make
    [root@server ~]# rpm -q gcc
    gcc-4.8.5-28.el7.x86_64
    [root@server ~]# rpm -q make
    make-3.82-23.el7.x86_64


2.进行解压缩
    ]# tar  -xf  /root/tools.tar.gz  -C  /usr/local
    ]# ls /usr/local/tools
    inotify-tools-3.13.tar.gz 
    3.进行tar解包 
    ]# tar -xf /usr/local/tools/inotify-tools-3.13.tar.gz -C /usr/local/          

    ]# ls  /usr/local/
    ]# cd   /usr/local/inotify-tools-3.13/
    ]# ls


4.运行configure脚本           
(1) 作用
作用1：检测当前系统是否安装gcc
作用2：指定安装位置与功能
作用3：生成Makefile文件（制作程序的大纲，做菜的菜谱）
    ]# cd   /usr/local/inotify-tools-3.13/
    ]# ./configure  --help   #查看帮助信息,大概浏览一下
    ]# ./configure  --prefix=/opt/myrpm #指定安装位置，此步骤不产生相应的目录         


(2) 常见的报错信息：gcc开发工具没有安装
checking for gcc... no
checking for cc... no
checking for cl.exe... no
configure: error: no acceptable C compiler found in $PATH
See `config.log' for more details.


5.进行make编译，变成可以执行的程序（放在内存中）
    [root@server ~]# cd /usr/local/inotify-tools-3.13/
    [root@server inotify-tools-3.13]# make
6.进行make install安装     
    [root@server ~]# cd /usr/local/inotify-tools-3.13/
    [root@server inotify-tools-3.13]# make   install 
    [root@server inotify-tools-3.13]# ls   /opt/
    [root@server inotify-tools-3.13]# ls   /opt/myrpm/
    [root@server inotify-tools-3.13]# ls   /opt/myrpm/bin/
```

---

## 2. 数据同步

### 2.1 rsync用法
1. 命令用法
    * rsync  [选项...]  源目录     目标目录
    
2. 同步与复制的差异
    * 复制：完全拷贝源到目标 
    * 同步：增量拷贝，只传输变化过的数据
    
3. rsync操作选项
    * -n：测试同步过程，不做实际修改
    * --delete：删除目标文件夹内多余的文档
    * **-a：归档模式，相当于-rlptgoD**
    * -v：显示详细操作信息 
    * -X：保持acl策略不变


### 2.2 本地同步

```
[root@server ~]# mkdir   /mydir   /todir
[root@server ~]# cp /etc/passwd    /mydir
[root@server ~]# touch   /mydir/1.txt
[root@server ~]# ls /mydir
]# rsync -avX   /mydir    /todir   #同步目录本身
]# ls   /todir

]# rsync -avX   /mydir/    /todir #同步目录内容
]# ls   /todir

]# touch   /mydir/2.txt
]# rsync -avX   /mydir/    /todir #同步目录内容
]# ls   /todir
]# echo  123 >  /mydir/1.txt
]# rsync -avX   /mydir/    /todir #同步目录内容
]# ls   /todir

]# mkdir   /mydir    /todir
]# echo haha >  /mydir/h.txt  
]# rsync  -avX  --delete   /mydir/      /todir/  #同步目录内容
]# ls   /mydir/
]# ls   /todir/
]# touch   /todir/a.txt          
]# ls  /todir/
]# rsync  -avX  --delete  /mydir/      /todir/
]# ls   /todir/
]# ls   /mydir/
```

### 2.3 远程同步
* 与远程的 SSH目录保持同步               
```
下行：rsync  [...]   user@host:远程目录    本地目录
上行：rsync  [...]   本地目录    user@host:远程目录
```

### 2.4 实时同步
* **虚拟机A生成公钥与私钥，虚拟机A将公钥传递给虚拟机B**

```
虚拟机A                 
1.虚拟机A生成公钥与私钥
    [root@server ~]# ssh-keygen         #一路回车
    [root@server ~]# ls    /root/.ssh/
    id_rsa(私钥)   id_rsa.pub(公钥)    known_hosts(记录曾经远程管理过的机器)
2．虚拟机A将公钥传递给虚拟机B
    ]# ssh-copy-id     root@192.168.88.2
    ]# rsync  -avX --delete   /mydir/    root@192.168.88.2:/mnt
```

### 2.5 监控目录变化的工具inotifywait

* 基本用法
    * inotifywait  [选项]  目标文件夹
* 常用命令选项
    * -m，持续监控（捕获一个事件后不退出）
    * -r，递归监控、包括子目录及文件
    * -q，减少屏幕输出信息
    * -e，指定监视的 modify、move、create、delete、attrib 等事件类别       


---

## 3. 数据库服务基础（数据库系统）

###  3.1 数据库是什么
* 数据库：存放**数据的仓库**；在数据库系统中，有很多**数据库**，在每个数据库中有很多的**表格**

### 3.2 常见的数据库管理系统
* 微软的SQL Server
* IBM 的 DB2
* 甲骨文的Oracle、**MySQL**
* 社区开源版**MariaDB**

>1. **MySQL与MariaDB是同一个人写的**；
>2. **数据库系统他不是简单的一个应用，<font color=red>已经上升到系统层面</font>，<font color=blue>两层结构（库--表格）</font>**

### 3.3 部署MariaDB数据库系统

#### 3.3.1 部署MariaDB

```
[root@server /]# yum  -y  install   mariadb-server
[root@server /]# systemctl   restart    mariadb
```

#### 3.3.2 MariaDB基本使用 
1. **Linux系统的管理指令不能使用**
2. 所有的数据库系统指令都必须**<font color=red>以 ; 结尾</font>**
3. 数据库系统的指令**大部分不支持tab补全**

```
1.
[root@server /]# mysql         #进入数据库系统
> create  database  nsd01;     #创建nsd01数据库
> show  databases;                #查看所有数据库
> drop   database   nsd01;    #删除数据库nsd01
> show  databases;               #查看所有数据库
> exit;
Bye
[root@server ~]#

2.
[root@server /]# mysql     #进入数据库系统
> use    mysql;              #切换到mysql数据库
> show   tables;          #查看当前库中所有表格
> show   databases;    #查看所有数据库
> use  test;             #切换到test数据库
> exit;
 
```

#### 3.3.3 恢复数据到数据库

```
Linux命令行]# mysql   test   <   /root/users.sql
Linux命令行]# mysql                 #进入数据库系统
MariaDB [(none)]> use test;        #切换到数据库test
MariaDB [test]> show tables;      #查看当前库有哪些表格
```

### 3.4 数据库“表格”层次的操作

#### 3.4.1 表格操作

* **增(insert)、删（delete）、改（update）、 查(select)**
* **表字段（表头）、表记录（表的内部数据）**


#### 3.4.2 查（select）

* 格式：**select    表字段,表字段,…… from   库名.表名;**

```
[root@server /]# mysql   
> use    test;
> select   *   from   base;        #查看base所有表字段内容
> select   *   from   location;    #查看location所有表字段内容
> select   name,password   from   base;   

> use  mysql;
> select   *   from    test.base;    

> use  test;
> select   id,name    from     base;

[root@server /]# mysql  
> use    test;    #切换到test库
查询密码为456的记录
> select  *   from    base  where   password='456';
查看id编号为4的记录
> select  *   from   base  where   id='4';
查询id编号为4并且密码为123的记录
> select  *  from  base  where  id='4'    and   password='123';
查询id编号为4或者密码为123的记录
> select  *  from  base   where  id='4'  or   password='123';
```

#### 3.4.3 增加（insert）

* **格式：insert  表名    values ('值','值','值');**

```
MariaDB [test]> insert   base  values('10','dc','789');
MariaDB [test]> insert   base  values('11','tcc','369');
MariaDB [test]> select   *   from base ;
```
#### 3.4.4 改（update）

* **格式：update  表名   set  表字段='新值' where  表字段='值'；**

```
> select   *  from  base ;
> update   base   set   password='8888'    where   id='1';
> select  *  from   base ;   

> update  base   set   password='9999'    where   id='2';
> select  *  from   base ;   
```

#### 3.4.5 删（delete）

```
> use   test;
> delete   from   base   where     id='4' ;
> select   *   from   base ;

> delete   from   base   where     id='3' ;
> select   *   from   base ;
```

### 3.5 为数据库系统管理员设置密码

#### 3.5.1 数据库root与linux root的区别

* 数据库系统管理员:对于数据库系统有最高权限，名字为root，能够登陆数据系统的用户信息，由mysql库中user表进行储存
* Linux系统管理员: 对于Linux系统有最高权限，名字为root，能够登陆Linux系统的用户信息，/etc/passwd进行储存

#### 3.5.2 为数据库系统管理员设置密码

```
1. 格式：mysqladmin  [-u用户名]  [-p[旧密码]]  password  '新密码'

2. 实例：
(1) 无旧密码
[root@server /]# mysqladmin -u  root  password  '456'
[root@server /]# mysql  -u   root   -p   #交互式进行登录
Enter password:
[root@server /]# mysql  -u root  -p456 #非交互式进行登录

(2) 已知旧密码修改新密码       
]# mysqladmin  -u   root  -p456  password   '123'
]# mysql  -u  root    -p123     
```

## 4. podman容器技术

### 4.1 容器基础概述
1. Linux中的容器是装应用的；
2. 容器就是将软件打包成标准化单元，用于开发、交付和部署；
3. 容器技术已经成为应用程序封装和交付的核心技术；

4. 优点
    * 相比于传统的虚拟化技术，容器更加简洁高效；
    * 传统虚拟机需要给每个VM安装操作系统；
    * 容器使用的共享公共库和程序 ；
    * 镜像是启动容器的核心，镜像由镜像仓库提供；
    * 在podman中容器是基于镜像启动的；
5. podman与容器的关系
    * podman是完整的一套容器管理系统；
    * podman提供了一组命令，让用户更加方便直接地使用容器技术，而不需要过多关心底层内核技术；
    
6. podman需要的软件支持
```
yum -y module install container-tools
``` 

### 4.2 镜像

#### 4.2.1 镜像的名称标识

* 每一个镜像都对应唯一的镜像 id；
* 镜像**名称（姓氏） + 标签（名字） = 唯一**；
* 每一个镜像都有标签，如果没写就是默认标签 latest；
* 我们在调用镜像的时候，如果没有指定标签也是 latest；
    
#### 4.2.2 查找镜像（需要访问互联网）
* podman  search  关键字；
    * 如：podman  search  httpd；
#### 4.2.3 下载镜像（需要访问互联网）
* podman  pull  镜像名称:标签
    * 如：podman   pull   localhost/myos:latest
#### 4.2.4 导入镜像
* podman  load  -i  备份文件.tar.gz
    * 如：podman   load  -i  /root/httpd.tar.gz
        
#### 4.2.5 查看镜像
* podman images
#### 4.2.6 删除镜像
* podman rmi 镜像名称:镜像标签

#### 4.2.7 镜像练习

```
1.镜像管理练习         
    ]# podman images        #查看当前有哪些镜像
    ]# podman  load   -i   /root/httpd.tar.gz     #导入镜像
    ]# podman images          #查看当前有哪些镜像
    ]# podman load  -i   /root/nginx.tar.gz     #导入镜像
    ]# podman load  -i   /root/myos.tar.gz     #导入镜像
    ]# podman images        #查看当前有哪些镜像
    
2. 镜像删除练习
    ]# podman  images           #查看当前有哪些镜像
    ]# podman   rmi   2f5        #按照镜像的ID值，删除镜像
    ]# podman  images           #查看当前有哪些镜像
    ]# podman load  -i   /root/myos.tar.gz            #导入镜像
    ]# podman  images           #查看当前有哪些镜像

    ]# podman   images       #查看当前系统可以使用的镜像
    ]# podman   rmi    localhost/myos:nginx    #删除镜像
    ]# podman   images

    ]# podman rmi  localhost/myos:latest      #删除镜像
    ]# podman   imag

```



### 4.3 podman容器技术

>**依赖文件：touch /etc/resolv.conf  #依赖此文件，保证此文件存在即可**

#### 4.3.1 使用容器
1. podman run 命令
    * podman  run  -选项   镜像名称:镜像标签   启动命令
   
2.  查看 run 的选项
    * podman  help  run
    * man  podman-run 
    * **run  =  创建 +  启动+ 进入；三合一的操作**

3. podman run 命令的选项
    * 选项 -i，交互式方式
    * 选项 -t，终端     
    * 选项 -d，后台运行
    * 选项 --name  容器名字

4. 启动容器，并进入容器
    * podman run -it myos:latest /bin/bash


5. **容器管理命令**
    * 启动容器
       * podman run –选项 镜像名称:镜像标签 启动命令
    * 查看容器
        * podman ps [ -a 所有容器id ] [ -q 只显示容器 id ]
    * 删除容器
        * podman rm 容器id
    * 容器管理命令启动、停止、重启
        * podman start|stop|restart 容器id
    * 进入容器
        * podman  exec   -it  容器id   启动命令


#### 4.3.2 容器练习

```
1. 容器初步练习                            
    ]# touch   /etc/resolv.conf  
    ]# podman  run  --name abc01 -it  localhost/myos:httpd   /bin/bash

    [root@2b0b7c62ab42 /]# cat /etc/redhat-release
    [root@2b0b7c62ab42 /]# useradd dc
    [root@2b0b7c62ab42 /]# id  dc
    [root@2b0b7c62ab42 /]# exit            #退出容器

    [root@rhel8 ~]# podman  ps   -a     #查看当前系统容器
    [root@rhel8 ~]# podman  start   abc01     #启动容器
    [root@rhel8 ~]# podman  exec  -it  abc01  /bin/bash   #进入容器
    [root@2b0b7c62ab42 /]# id  dc
    [root@2b0b7c62ab42 /]# exit            #退出容器

    [root@rhel8 ~]# podman  rm  -f   abc01    #强制删除容器abc01
    

2. 容器放入后台练习                           
    ]# podman  rm  -f  abc01     #强制删除容器abc01

    ]# podman run --name  abc01  -d  localhost/myos:httpd 

    ]# podman  ps  -a        #查看当前系统有哪些容器
    ]# podman  exec   -it  abc01    /bin/bash   #进入abc01容器
    [root@962aa837e17b /]# useradd  tc
    [root@962aa837e17b /]# id tc     
    [root@962aa837e17b /]# exit     

    ]# podman  ps  -a      #查看当前系统有哪些容器
    ]# podman  exec   -it    abc01   /bin/bash #进入abc01容器
    [root@962aa837e17b /]# id tc
    [root@962aa837e17b /]# exit
    ]# podman  ps  -a             #查看当前系统有哪些容器
    ]# podman  rm  -f  abc01     #强制删除容器abc01
```

#### 4.3.3 容器进阶-对外发布容器服务

* 容器可以与宿主机的端口进行绑定
* 从而把宿主机变成对应的服务,不用关心容器的IP地址
* 我们使用 -p 参数把容器端口和宿主机端口绑定
* 同一宿主机端口只能绑定一个容器服务
* -p  [可选IP]:宿主机端口:容器端口
* 例如:把宿主机变成 apache
    * podman run -d -p 80:80 myos:httpd
* 例如:把宿主机变成 nginx
    * podman run -d -p 80:80 myos:nginx

```
1. 容器放入后台,端口绑定练习    
    ]# podman  run  --name  nsdweb   -p   80:80         -d   localhost/myos:httpd    

    [root@rhel8 ~]# podman ps -a
    [root@rhel8 ~]# podman exec -it nsdweb /bin/bash

    [root@5b69bf6956b0 html]# echo wo shi nsdweb > /var/www/html/index.html 
    [root@5b69bf6956b0 html]# exit
    exit

    [root@rhel8 ~]# curl   192.168.88.4
    wo shi nsdweb
    [root@rhel8 ~]#
```

#### 4.3.4 容器进阶-容器共享卷

* podman容器不适合保存任何数据
* podman可以映射宿主机文件或目录到容器中
    * 目标对象不存在就自动创建
    * 目标对象存在就直接覆盖掉
    * 多个容器可以映射同一个目标对象来达到数据共享的目的
* 启动容器时，使用 -v 映射参数
    * podman run -d  -v  宿主机对象:容器内对象   镜像名称:标签

```
1. 容器终极练习             
    ]# podman   rm   -f    nsdweb       #强制删除容器
    ]# mkdir    /webroot
    ]# echo wo  shi  niuniu   >    /webroot/index.html

    ]# podman run   --name  nsdweb    -p 80:80                                    -v  /webroot:/var/www/html   -d  localhost/myos:httpd 

    [root@rhel8 ~]# curl   192.168.88.4          
    wo shi niuniu             
```

#### 4.3.5 容器进阶-管理系统服务

* **systemd**一个更高效的系统&服务管理器
    * 开机服务并行启动，各系统服务间的精确依赖
    * 服务目录：/usr/lib/systemd/system/
    * 主要管理工具：systemctl
    
* 手动方式：
   * podman   start   nsdweb    #启动容器
   * podman   stop   nsdweb    #停止容器
* systemd方式：
   * systemctl   start   nsdweb    #启动容器
   * systemctl   stop   nsdweb    #停止容器
* systemd管理方式思路：
   * 用户--systemctl--> systemd--服务配置文件--> 容器启动
   
```
•管理员服务文件默认路径
    –/usr/lib/systemd/system/
•生成服务启动配置文件
    --files：生成文件类型
    podman  generate  systemd   --name  容器名  --files  
•重新加载服务启动配置文件
    systemctl  daemon-reload
    
1. 容器之光练习（必须是相对路径，当前路径必须是/usr/lib/systemd/system，容器必须正在运行）
    ]# cd   /usr/lib/systemd/system   
    ]# podman   ps   -a
    ]# podman  generate   systemd   --name   nsdweb   --files
    ]# vim   container-nsdweb.service  

    ]# systemctl   daemon-reload     #重新加载服务配置文件
    ]# systemctl   daemon-reload
    ]# podman   stop    nsdweb        
    ]# podman   ps    -a
    ]# systemctl  start   container-nsdweb
    ]# podman   ps  -a
    ]# systemctl   enable   container-nsdweb     #设置开机自启
```

---