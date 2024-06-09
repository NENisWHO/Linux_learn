# 2_1 Linux基础操作

[TOC]

## 0. 参考
>https://www.linuxcool.com/rpm

## 1. 装机后的一些小命令查看系统的信息

1. cat（concatenate files and print）：其功能是在终端设备上显示文件内容。
    - 语法：cat 参数 文件名
    - cat /etc/redhat-release    #参看红帽系统的版本信息
    - cat /etc/os-release
    - cat /proc/meminfo          #查看内存信息
    - cat /proc/partitions         #查看分区信息
    - cat /etc/shadow 是 Linux 系统中存储用户加密密码的文件，每行对应一个用户的加密信息。该文件只有系统管理员 root 用户可以访问。
    
2. uname（UNIX name）：其功能是查看系统主机名、内核及硬件架构等信息。如果不加任何参数，默认仅显示系统内核名称（相当于-s参数）的作用。
    - 语法：uname 参数
    - uname -a：显示系统所有信息
    - uname -r：显示内核发行版本号
    - uname -s：显示内核名称
    - uname -n：显示主机名

3. lsb_release （Linux Standard Base release）：功能是用于查看LSB版本信息，帮助Linux系统运维人员快速了解系统情况。

4. free：功能是显示系统内存使用量情况，包含物理内存和交换内存的总量、使用量、空闲量情况。
    - 语法：free 参数
    - free -h
    
5. who：功能是用于显示当前登录用户信息，包含登录的用户名、终端、日期时间、进程等信息，帮助运维人员了解当前系统的登入用户情况。
    - 语法：who 参数
    - who -r：显示当前运行级别
    - who -a：显示所有信息
    
6. whoami（Who am i）：其功能是用于显示当前用户名

7. init（initialize）：其功能是切换系统运行级别。
    - 语法：init 参数
    
    | 参数 |      功能      |
    | :--: | :-----------: |
    |  0   |      关机      |
    |  1   |     单用户     |
    |  2   |     多用户     |
    |  3   | 完全多用户模式 |
    |  4   |     无功能     |
    |  5   |   图形化界面   |
    |  6   |      重启      |
    
8. runlevel：命令是读取/var/run/utmp/文件或指定的其他文件，检索其中最近的运行级记录，显示系统先前与当前的运行级，

9. ifconfig（network interfaces configuring）：其功能是显示或设置网络设备参数信息。

10. tty（Teletype（电传打字机））：打印出当前终端的名字

## 2. 基础命令

### 2.1 初识基本命令

1. id：查看用户与用户组信息。UID是用户身份的唯一识别码，GID是用户组唯一的识别码。
    * -u 显示用户的ID（UID）
    
2. 终端
    * 物理终端：/dev/console
    * 虚拟终端：tty
    * 伪终端：pts

3. 查看shell
    * echo $SHELL
    * cat /etc/shells
    
4. 修改**终端提示符**（PS1）
    * 列出PS1：echo $PS1
    * 修改PS1：vim /etc/profile.d/env.sh
    * 或者修改家目录下的 .profile文件

5. pstree：pstree命令来自英文词组“display a tree of processes”的缩写，其功能是用于以树状图形式显示进程信息，帮助管理员更好地了解进程间的关系。

6. type：判断是内/外命令
    -a 显示所有包含名称为 NAME 的可执行文件的位置；包括别名、内建和函数。
    
7. help：列出内部命令清单

8. enable：用来启动或关闭shell的内建命令。
    -n 关闭指定的shell的内建命令（不加-n可重新启动关闭的指令）
    -all 显示shell所有关闭与启动的指令
    
9. which：查看外部命令在磁盘上的路径

10. whersis： 查看外部命令在磁盘的位置及其help文档路径

11. echo $PATH：查看当前环境变量

12. hash：管理命令运行时查询的哈希表。（命令缓存）
    * -r 清空缓存
    * -l 显示hash表中的命令
    
13. alias（别名）：设置命令名信息
    * -p 显示系统中的已有的命令别名
    * 设置一个别名举例子：**alias cdnet='cd /etc/sysconfig/network-scripts'**
    * 个人用户永久生效配置/home/.bashrc
    * 所有用户生效：/etc/.bashrc
    * 删除别名：unalias
    * 别名与内部命令冲突时：比如有个echo的别名
         - 以下方式启用内部命令
         - \echo
         - 'echo'
         - /bin/echo
         
14. 命令的执行顺序：

**别名->内部命令->外部hash表->外部$PATH**

</br>
15. 取消或结束命令的执行
    * ctrl+c
    * ctrl+d
    
16. 一行多条命令：' ; '分割
    - 如 learn@192:~$ :who;ls -l;date

17. 多行执行一条命令：' \ '分割

18. lshw：列出硬件信息

19. hexdump（hexadecimal dump）：其功能是以多种进制格式查看文件内容。
    * -b 八进制显示
    * -c 使用单字节字符显示
    
20. 显示语言编码
    * echo $LANG
    * localectl set-locale LANG=zh_CN.UTF-8
    * localectl set-locale LANG=en_us.UTF-8
    * localectl：用于查询与修改系统的本地化(locale)与键盘布局的设置。

21. w：w命令来自英文单词“who”的缩写，其功能是用于显示已登录用户的信息。

22. rpm：redhat package manager的缩写，中文译为“红帽软件包管理器”，其功能是在Linux系统下对软件包进行安装、卸载、查询、验证、升级等工作，常见的主流系统（如RHEL、CentOS、Fedora等）都采用这种软件包管理器，推荐用固定搭配“rpm-ivh 软件包名”安装软件，而卸载软件则用固定搭配“rpm -evh 软件包名”，简单好记又好用。

23. fg 启动由ctrl+z暂停的进程
    * **fg命令来自英文单词“foreground”，中文译为“前景”，其功能是用于将作业放到前台运行。在Linux系统中可以使用bg命令将作业放到后台运行，同理也能够使用fg命令将已经在后台运行或被挂起的作业放回前台终端继续运行。**

24. wc （word count）：统计文件的字节数、单词数、行数。
    * -c  统计字节数
    * -l   统计行数
    * -m 统计字符数
    * -w  统计单词数


### 2.2 日期和时间

1. 系统时间和硬件时间
    * 系统时间：date
    * 硬件时间（root用户下）：hwclock，clock
        -s 系统以硬件为准
        -w 硬件以系统为准
    * 同步与远程服务器的时间：ntpdate

2. timedatectl： l命令来自英文词组time date control的缩写，其功能是设置系统时间与日期。


## 3. 帮助命令
    
>1. whatis
>2. command --help
>3. man and info
>4. /usr/share/doc
>5. 查官网信息

1. whatis：用于查询一个命令执行什么功能（简单介绍），并将查询结果打印到终端上。
    
2. 在whatis没有输出到终端时，需要使用**mandb**命令：man用于初始化或手动更新通常由man维护的索引数据库缓存，缓存包含与手动页面系统的当前状态相关的信息，其中存储的信息由mandb实用程序用于提高其速度和功能。

3. 查看内/外命令帮助
    1. 内：help command / man bash
    2. 外：command --help 
    
4. 详细查看 man


## 4. 关机、重启
1. 关机：halt、poweroff
2. 重启：reboot
3. 关机或者重启：shutdown 
        -r   重启 
        -h  关机  
        -c  取消


## 5. 设置主机名

1. 临时修改：hostname <newhostname>
2. 彻底修改：hostnamectl set-hostname <newhostname>
3. 修改文件：vim  /etc/hosts 或者 vim  /etc/hostname


## 6.  rm删除

* **<font color=red>rm</font>**：其功能是删除文件或目录，一次可以删除多个文件，或递归删除目录及其内的所有子文件。

    -r  **递归删除**
    -f  **强制删除不提示**
    -d **仅删除空目录**
    -v **显示删除的执行过程** 

## 7. 软件包的管理RPM、 YUM

1. RPM软件包管理

|   封包类型   |                       说明                        |
| :---------: | :-----------------------------------------------: |
|  rpm软件包   |               .rpm，适用于RetHat系列               |
|  deb软件包   |               .deb，适用于Debian系列               |
| 源代码软件包 | .tar.gz、.tar.bz2 压缩包提供，包含程序的原始代码文件 |
|     其他     |         install.sh、setup、\*.bin、\*.pl等         |
   
2. RPM包的一般安装位置

|             文件类别             |             默认安装位置             |
| :------------------------------: | :--------------------------------: |
|     普通执行<mark>程序</mark>     |         /usr/bin  or  /bin         |
| 服务器<mark>程序</mark>、管理工具 |        /usr/sbin  or  /sbin        |
|             配置文件             |        /etc  or  /etc/软件名        |
|             日志文件             |   /var/log/  or  /var/log/软件名/   |
|        程序文档、man手册页        | /usr/share/doc  or  /usr/share/man |

3. 显示是否安装了rpm软件
    - **rpm：i旁边有q就是查询information的意思，没有q就是install的意思**
    - 安装：rpm -ivh    软件包名
    - 卸载：rpm -evh   软件包名
    * rpm -q 软件名    （不是软件包名）查看软件是否安装了
    * rpm -ql 软件名      查看这个软件在安装时将文件放在了那些目录下
    * rpm -qpl rpm包(run目录下的包)   还没安装，如果安装的话会安装啥
    * rpm -qpi rpm包                           还没安装，显示软件包的信息    
    * RPM-GPG-KEY-redhat-release     红帽签名（/run/media/learn/RHEL-8-0-0-BaseOS-x86_64）
    * 导入红帽签名文件： rpm --import /run/media/learn/RHEL-8-0-0-BaseOS-x86_64/RPM-GPG-KEY-redhat-release

4. rpm命令无法解决依赖关系，yum可以解决依赖关系
    * yum（yellowdog updater modified）
      * 基于RPM包构建的软件更新机制
      * 自动解决软件包依赖关系
      * 所有软件包由集中的YUM软件仓库提供  
    </br>
    * 仓库清单：/run/media/learn/RHEL-8-0-0-BaseOS-x86_64/AppStream/repodata
    * yum工作流程
        *  **yum-->读取/etc/yum.repos.d/\*.repod配置文件内容-->从而找到仓库的具体位置**
    * 查看仓库信息：yum repolist -v  
    * yum安装：      yum install 软件名 （-y 不用再询问，我默认yes）
    * yum卸载：      yum remove 软件名 （-y，不用再询问，我默认yes）
```shell
[]                 #名字--仓库标识
name=              #仓库描述信息
baseurl=           #仓库位置url
enable=            #能不能用 1可用，0不可用
gpgcheck=          #是否检查红帽签名 1检查，0不检查
gpgkey=            #仓库的签名文件路径
```

## 8. IP知识

1. TCP/IP协议简介
    * TCP/IP是最广泛支持的通信协议集合
        * 包括大量internet应用中的标准协议
        * 支持跨网架构、跨操作系统平台的通信
    * 主机与主机之间通信的三要素
        * ip地址（ip address）
        * 子网掩码 （subnet mask）
        * ip路由（ip router）
        
2. IP地址的概括
    * 作用：唯一用来标识一个节点的网络地址
    * 地址组成：8+8+8+8，32位；为**网络位+主机位**

3. IP地址的概括
    * ip的分类
        * A：1~127       255.0.0.0
        * B：128~191    255.255.0.0
        * C：192~223  255.255.255.0
        * D（组播）：224~239
        * E（科研）：240~254
        * 127.0.0.1    常做本机回环地址
        
4. 交换机：将多个主机连再一起，可以实现通信
5. DHCP动态主机配置协议（配置好再使用）
6. DNS域名系统，作用是将域名解析成IP地址
7. 路由器：解决不同网络的通信，这里延申出网关的概念，
8. 网关（gateway）：从一个网络连接到另外一个网络的“关口”；通常是一台路由器，或者防火墙/接入服务器；例如路由器两端的网关为**“192.168.1.255”，“192.168.2.255”**。



## 9. 查看一些linux的信息

1. 查看硬件信息：lshw
2. 查看硬盘信息：lsblk
3. 查看cup信息：lscpu
4. 查看内存信息：cat /proc/meminfo
5. 查看网络信息：ifconfig
6. 查看主机名：hostname
7. 查看系统信息：uname -a

## 10. 命令行快捷键

1. ctrl+c：结束正在运行的命令
2. Esc+. 或者 Alt+. ：黏贴上一个命令的参数
3. ctrl+l：清空整个屏幕
4. ctrl+u：从光标处清空至行首
5. ctrl+w：往回删除一个单词（以空格界定）

## 11. 光盘挂载
0. 现在是临时挂载操作
1. 虚拟机光驱设备：**/dev/cdrom （这是个软连接，连接到sr0）---->  /dev/sr0**
2. linux挂载光盘文件过程：**光盘--->光驱设备--->访问点(目录)**

```
0. 挂载的意义：让目录成为设备的访问点
1. 创建空目录：mkdir /dvd
2. 挂载：mount /dev/cdrom /dvd
3. 卸载：umount /dvd
4. 注意事项：
    * 卸载：当前所在的路径是挂载点目录 
5. mount直接敲mount查看挂载点
```


## 12. 归档及压缩

### 1 .tar、gzip、bzip2
1. **tar是归档及压缩工具**
* 语法格式：tar [参数] 打包文件名 源文件

|   参数   |                        含义                         |
| :------: | :-------------------------------------------------: |
|    -c    |              生成档案文件，创建打包文件               |
|    -v    |            列出归档解压的详细过程，显示进度            |
|    -f    | 指定档案文件名称，f后面一定是.tar文件，所以必须放在最后 |
|    -t    |                 列出档案中包含的文件                  |
|    -x    |                     解开档案文件                     |
| -C(大写) |                       指定路径                       |
|    -z    |              调用.gz格式工具进行压缩处理              |
|    -j    |             调用.bz2格式工具进行压缩处理              |
|    -J    |              调用.xz格式工具进行压缩处理              |
     
2. **tar归档操作：只进行打包/解包**
    * tar -cvf    创建归档文件
    * tar -xvf    解除归档文件
    * tar -tvf    查看归档文件内容
    
3. **tar压缩操作：即打包又压缩**
    * tar -czvf    生成 **.tar.gz**
    * tar -cjvf     生成 **.tar.bz2**
    * tar -cJvf     生成 **.tar.xz**

### 2. zip和unzip
>**通过zip压缩文件的目标文件不需要指定扩展名，默认扩展名为zip。**

* 压缩文件：zip -r 目标文件(没有扩展名) 源文件
* 解压文件：unzip -d 解压后目录文件 压缩文件


## 13. find查找文件
### 1. find基础
* 语法：find [目录] [条件]
* 常用条件：
    * -type    类型（f、d、l）
    * -name   ”文档名称“
    * -size      +|-文件大小（k、M、G）
    * -user       用户名（所有者）
    * -mtime    修改时间 
   
### 2. find高级
* find 高级使用：额外操作
    * **find /boot -size +10M -exec  cp  {}  /mnt \;**
        * 额外操作的开始：-exec
        * 额外操作的结束：\;
        * 前面find命令查找的数据：{}
        
## 14. 软硬链接
1. 软链接
* 格式：ln -s /路径/源数据    /路径/快捷方式名称
* 软链接优势：可以针对目录与文件制作快捷方式，支持跨分区
* 软链接缺点：源数据消失，快捷方式失效

2. 硬链接
* 格式：ln   /路径/源数据    /路径/快捷方式的名称    #硬链接
* 硬链接优势：源数据消失，快捷方式仍然有效
* 硬链接缺点：只能针对文件制作快捷方式，不支持支持跨分区

## 15. 系统进度

1. pstree

```
pstree查看进程(Processes Tree)    
•常用命令选项
    -p：列出对应进程的PID编号 
    -a：显示完整的命令行   
systemd(PID永远为1)：所有进程的父进程（上帝进程）
[root@localhost ~]# pstree     #显示正在运行的所有进程
[root@localhost ~]# pstree  -p lisi #显示lisi用户开启的进程
bash(9609)───vim(9656)
[root@localhost ~]# pstree  -a  lisi   
bash
  └─vim haha.txt
[root@localhost ~]# pstree  -ap  lisi
```
2. ps

```
ps — Processes Snapshot
    –格式：ps  [选项]...
•常用命令选项
    –aux：显示当前终端所有进程（a）、当前用户在所有终端下的进程（x）、以用户格式输出（u）
    -elf：显示系统内所有进程（-e）、以长格式输出（-l）信息、包括最完整的进程信息（-f）

•ps  aux 操作
    –列出正在运行的所有进程，显示进程信息非常详细

•ps  -elf 操作
    –列出正在运行的所有进程，显示进程父进程信息
    –PPID为父进程的PID
```

3. top

```
top 动态的查看工具
    –格式：top  [-d  刷新秒数]  [-U  用户名]

    [root@localhost ~]# top   -d   1
    按大写P进行CPU排序
    按大写M进行内存排序   
```

4. pgrep —— Process Grep

```
pgrep — Process Grep
    –用途：pgrep  [选项]...  查询条件
    •常用命令选项
    -l：输出进程名，而不仅仅是 PID
    -u：检索指定用户的进程
    -x：精确匹配完整的进程名 
```

5. 干掉进程

```
–Ctrl+c 组合键，中断当前命令程序
–kill  [-9]  PID... 、kill  [-9]  %后台任务编号
–killall  [-9]  进程名...
-pkill    [-9]  查找条件   #包含就算
```

6. 控制进程

```
进程的前后台调度                         
•&符号：正在运行的状态放入后台
•Ctrl + z 组合键
    –挂起当前进程（暂停并转入后台）
•jobs 命令
    –查看后台任务列表
•fg 命令
    –将后台任务恢复到前台运行
•bg 命令
    –激活后台被挂起的任务
```
