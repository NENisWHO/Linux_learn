# 9_1 Linux 网络管理

[toc]

---

## 1. 构建yum仓库

<br/>

1. 将光驱挂载到自建文件夹下
 
```
[root@localhost ~]# mkdir     /mydvd
[root@localhost ~]# mount   /dev/cdrom    /mydvd [root@localhost ~]# ls   /mydvd
```
<br/>

2. 手写客户配置文件

```
[root@localhost ~]# rm  -rf   /etc/yum.repos.d/*
[root@localhost ~]# vim   /etc/yum.repos.d/mydvd.repo
[centos]
name=haha
baseurl=file:///mydvd
enabled=1
gpgcheck=0
[root@localhost ~]# yum repolist
[root@localhost ~]# yum  -y    install   dhcp  
```

<br/>

3. 开机自动挂载

```
]# blkid  /dev/cdrom   #查看 光驱设备文件系统类型
]# vim   /etc/fstab   #添加一行配置
/dev/cdrom   /mydvd   iso9660   defaults   0  0
]# umount   /mydvd    
]# mount  -a     #进行检测
]# ls   /mydvd
]# yum -y install   bind   #测试安装软件包
```
<br/>

4. 当配置的主机作为样板机要克隆时，要修改/etc/fstab下的UUID

```
* UUID是机器的唯一标识

[root@localhost ~]# df  -h  /boot  #查看设备挂载情况
文件系统        容量  已用  可用 已用% 挂载点
/dev/sda1      1014M  172M  843M   17% /boot
[root@localhost ~]# blkid  /dev/sda1   
/dev/sda1: UUID="8e57ee09-0d60-4da9-87a0-83bb4a62587d" TYPE="xfs"
[root@localhost ~]# vim    /etc/fstab    #vmware虚拟机
/dev/sda1    /boot        xfs     defaults        0 0
[root@localhost ~]# vim   /etc/fstab    #KVM虚拟机
/dev/vda1   /boot       xfs     defaults        0 0
[root@localhost ~]# reboot    #重启系统
[root@localhost ~]# yum  repolist   #检测yum仓库
```
<br/>

5. yum常见错误：清空/var/run/yum.pid文件内容

```
[root@localhost ~]# yum  repolist 
已加载插件：fastestmirror, langpacks
/var/run/yum.pid 已被锁定，PID 为 2446 的另一个程序正在运行。
Another app is currently holding the yum lock; waiting for it to exit...
  另一个应用程序是：PackageKit
    内存： 33 M RSS （378 MB VSZ）
    已启动： Fri May 13 09:37:12 2022 - 00:07之前
    状态  ：睡眠中，进程ID：2446
Loading mirror speeds from cached hostfile
源标识                   源名称                   状态
centos                   linux                    10,072
repolist: 10,072
[root@localhost ~]# > /var/run/yum.pid   #清空文件内容
[root@localhost ~]# yum clean all   #清空yum缓存
[root@localhost ~]# yum repolist    #列出仓库信息
```

---

## 2. 配置主机名

* 永久设置主机名
    * 方法一：敲命令hostnamectl set-hostname xxxxxxx
    * 方法二：vim /etc/hostname
    * 查看主机名：终端输入hostname
    
---

## 3. 配置网络参数之IP地址与子网掩码、网关地址

### 3.1 修改网卡命名规则（eth0，eth1，eth2）

```
]# ifconfig   |    head    -2
ens33: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        ether 00:0c:29:8a:72:4f  txqueuelen 1000  (Ethernet)

]# vim   /etc/default/grub      #内核引导文件
……..此处省略一万字
GRUB_CMDLINE_LINUX="…….. quiet   net.ifnames=0  biosdevname=0"
……..此处省略一万字                            
]# grub2-mkconfig  -o  /boot/grub2/grub.cfg  #重新生成网卡命名的规则
]# reboot      #重启系统
]# ifconfig   |   head   -2
eth0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 192.168.81.132  netmask 255.255.255.0  broadcast 192.168.81.255
```

### 3.2 配置地址

>三种方式配置地址：**1.nmtui；2.nmcli；3.修改配置文件**

#### 3.2.1 nmcli

```
1. nmcli命令的网卡命名，删除错误网卡命名
    [root@server ~]# nmcli  connection   show     #查看
    [root@server ~]# nmcli  connection   delete   ens33
    [root@server ~]# nmcli  connection   show
    [root@server ~]# nmcli  connection   show
    [root@server ~]# nmcli  connection  delete  有线连接\ 1 
    [root@server ~]# nmcli  connection   show
    
2. nmcli命令的网卡命名，添加新的网络命名
    [root@server ~]# nmcli connection  add  type  ethernet      ifname  eth0    con-name   eth0
    解析： nmcli connection 添加   类型   以太网设备
    网卡设备名为eth0    nmcli命令的命名为eth0

    [root@server ~]# nmcli   connection   show
    [root@server ~]# cat   /etc/sysconfig/network-scripts/ifcfg-eth0    #简单查看生成的网卡配置文件内容

3. 利用nmcli修改IP地址、子网掩码、网关地址
    [root@server ~]# nmcli connection modify  eth0    
    ipv4.method    manual                          
    ipv4.addresses   192.168.88.77/24                
    ipv4.gateway   192.168.88.200               
    connection.autoconnect    yes
    命令解析：
    [root@server ~]# nmcli connection   修改   外号   
    ipv4.方法    手工配置                          
    ipv4.地址   192.168.88.77/24                
    ipv4.网关   192.168.88.200               
    每次开机自动启用以上所有参数
    [root@server ~]# nmcli connection up eth0     #激活
    [root@server ~]# ifconfig   |   head   -2

    [root@server ~]# route   -n        #查看网关地址信息
```

#### 3.2.2  配置文件修改IP地址、子网掩码、网关地址

```
]# vim   /etc/sysconfig/network-scripts/ifcfg-eth0
.....此处省略一万字......
IPADDR=192.168.88.240
PREFIX=24
GATEWAY=192.168.88.222
]# ifdown  eth0          #停用设备（名字为网卡实际名字）
]# ifup  eth0              #启用设备（名字为网卡实际名字）
]# ifconfig  |  head  -2
```

---

## 4. 远程管理（Linux 与 linux）

> SSH协议

1. 软件包安装

```
[root@server /]# rpm  -qa   |   grep   openssh
openssh-7.4p1-16.el7.x86_64
openssh-server-7.4p1-16.el7.x86_64
openssh-clients-7.4p1-16.el7.x86_64

[root@server ~]#ls /usr/sbin/sshd#提供远程管理功能的程序
/usr/sbin/sshd
[root@server ~]# pgrep -l  sshd   #搜索sshd进程
1181 sshd
```

2. 远程登录工具ssh

```
[root@server /]#  ssh    root@192.168.88.2
………necting (yes/no)? yes
root@192.168.88.2's password:        #输入密码
[root@pc2 ~]# touch   /root/hahaxixi.txt
[root@pc2 ~]# exit
登出
Connection to 192.168.88.2 closed.
[root@server /]# cat   /root/.ssh/known_hosts  #记录曾经远程管理的机器
```

3. 数据传递工具scp=ssh+cp

```
* scp  [-r]  用户名@服务器:路径      本地路径
* scp  [-r]  本地路径    用户名@服务器:路径

虚拟机A：                 
]# scp    /etc/passwd       root@192.168.88.2:/root
]# scp  -r    /home       root@192.168.88.2:/root
]# scp    root@192.168.88.2:/etc/shadow        /mnt
虚拟机B：                      
]# ls    /root
```

4. 实现ssh远程管理无密码验证

```
虚拟机A：
1.生成公钥(锁)与私钥(钥匙)进行验证 
[root@server ~]# ssh-keygen      #一路回车
…….save the key (/root/.ssh/id_rsa):   #回车 设置默认保存位置
……..assphrase):     #回车 设置密码为空
…….. again:     #回车 设置密码为空
[root@server ~]# ls   /root/.ssh/
id_rsa(私钥)    id_rsa.pub(公钥)     known_hosts
2.将公钥(锁)传递给虚拟机B 
[root@server ~]# ssh-copy-id     root@192.168.88.2 
[root@server ~]# ssh     root@192.168.88.2     #测试无密码
[root@pc2 ~]# exit
登出
Connection to 192.168.88.2 closed.
[root@server ~]#
虚拟机B          
[root@pc2 ~]# ls    /root/.ssh/
authorized_keys(别的机器传递过来的公钥)    known_hosts
[root@pc2 ~]#
```

---

## 5. 配置网络参数之DNS服务器地址

* **DNS服务器：负责域名解析的服务器，将域名解析为IP地址**
* **/etc/resolv.conf:最终有效配置文件**

```
]# echo nameserver   99.100.200.38  > /etc/resolv.conf
]# cat   /etc/resolv.conf
nameserver    99.100.200.38

]#  >  /etc/resolv.conf    #清空此文件内容，为构建Web服务器做准备
]#  cat   /etc/resolv.conf
```

---

## 6. 日志管理

1. 日志的功能
    * 系统和程序的“日记本”
        * 记录系统、程序运行中发生的各种事件
        * 通过查看日志，了解及排除故障
        * 信息安全控制的“依据”
        
2. 日志的管理
    * 由系统服务rsyslog统一记录/管理
        * 日志消息采用文本格式
        * 主要记录事件发生的时间、主机、进程、内容
        
3. 常见的日志问价

|      日志文件      |            主要用途            |
| :---------------: | :---------------------------: |
| /var/log/messages | 记录内核消息、各种服务的公共消息 |
|  /var/log/dmesg   |    记录系统启动过程的各种消息    |
|   /var/log/cron   |   记录与cron计划任务相关的消息   |
| /var/log/maillog  |      记录邮件收发相关的消息      |
|  /var/log/secure  |   记录与访问限制相关的安全消息   |

---

## 7. 登录用户查看

* users、who、w 命令
    * 查看已登录的用户信息，详细度不同
* last、lastb 命令
    * 查看最近登录成功/失败的用户信息

---    

## 8. Linux内核定义的事件紧急程度

* 分为 0~7 共8种优先级别
* 其数值越小，表示对应事件越紧急/重要

|                    |                          |
| :----------------: | :----------------------: |
|  0  EMERG（紧急）  | 会导致主机系统不可用的情况 |
|  1  ALERT（警告）  | 必须马上采取措施解决的问题 |
|  2  CRIT（严重）   |      比较严重的情况       |
|   3  ERR（错误）   |       运行出现错误        |
| 4  WARNING（提醒） |  可能会影响系统功能的事件  |
| 5  NOTICE（注意）  |   不会影响系统但值得注意   |
|  6  INFO（信息）   |         一般信息          |
|  7  DEBUG（调试）  |    程序或系统调试信息等    |

---

## 9. ip 命令

1. 查看ip地址
    * ip address show
    * ip a s
    
2. 临时添加ip地址
    * ip address add 192.168.10.1/24 dev eth0
    * ip   a   a   192.168.20.1/24   dev  eth0
    
3. 删除临时ip地址
    * ip  address  del  192.168.10.1/24   dev    eth0
    
4. ping测网络连接
    * -c 包个数
    * ping -c  2  192.168.88.240
    
---

## 10. 系统安全保护

1. **SELinux的运行模式**
    * enforcing（强制）
    * permissive（宽松）
    * disabled（彻底禁用）
    * 任何模式变成disabled模式，都要经历重启系统
  
2. **切换运行模式**
    * 获取状态：getenforce
    * 临时切换：setenforce  1或0
        * [root@server /]# setenforce 0  #修改当前运行模式
    * 固定配置：/etc/selinux/config 文件
        * [root@server /]# vim    /etc/selinux/config  
           SELINUX=permissive      #需改配置
           
## 11. 构建基础服务

### 11.1 构建Web服务
* Web服务：提供一个页面内容的服务
* 提供Web服务的软件：httpd、Nginx、tomcat
* http协议：超文本传输协议

```
1.安装软件包          
    [root@server ~]# yum  -y  install  httpd
2.运行提供Web服务程序
    ]# /usr/sbin/httpd         #绝对路径运行程序
    ]# pgrep  -l  httpd        #查看进程信息
4.书写一个页面文件         
    ]# vim   /var/www/html/index.html
    haha阳光明媚
5.本机浏览器访问测试        
    ]# curl   192.168.88.240
    haha阳光明媚
```

### 11.2 构建FTP服务
* FTP：文本传输协议
* 实现FTP服务功能的软件：vsftpd
* 默认共享数据的主目录：/var/ftp/

```
1.安装软件包       
    [root@server ~]# yum  -y  install  vsftpd
2.运行程序
    [root@server ~]# /usr/sbin/vsftpd
    [root@server ~]# pgrep  -l  vsftpd #查看进程信息
    [root@server ~]# touch  /var/ftp/dcc.txt
3.本机访问测试
    [root@server ~]# curl  ftp://192.168.88.240
    -rw-r--r--    1 0   0    0 May 16 06:42 dcc.txt
    drwxr-xr-x    2 0    0   6 Oct 13  2020 pub
```

---

## 12. 防火墙策略

* 作用：**隔离，严格过滤入站，放行出站**
* 系统服务：firewalld ---->iptables(底层防火墙)
* 管理工具：**firewall-cmd**、firewall-config

```
根据所在的网络场所区分，预设区域:
    public：仅允许访问本机的ssh、dhcp、ping服务
    trusted：允许任何访问
    block：拒绝任何来访请求，明确拒绝客户端
    drop：丢弃任何来访的数据包，不给任何回应
```
* 防火墙判定原则：
    1. 查看客户端请求中**来源IP地址**，查看自己所有区域中规则，那个区域中有该源IP地址规则，则进入该区域
    2. 进入默认区域（默认情况下为public）
    
### 12.1 防火墙默认区域的修改

```
虚拟机A                           
]# firewall-cmd    --get-default-zone   #查看默认区域
虚拟机B
]# curl      192.168.88.240    #失败
]# curl      ftp://192.168.88.240      #失败
]# ping    -c2    192.168.88.240        #成功

虚拟机A：修改默认区域
]# firewall-cmd   --set-default-zone=trusted
虚拟机B
]# curl      192.168.88.240    #成功
]# curl      ftp://192.168.88.240    #成功
```

### 12.2 防火墙public区域添加规则

```
虚拟机A：添加允许的协议
]# firewall-cmd    --set-default-zone=public
]# firewall-cmd  --zone=public  --add-service=http   
]# firewall-cmd   --zone=public   --list-all
虚拟机B
]# curl   http://192.168.88.240    #成功
]# curl   ftp://192.168.88.240     #失败

虚拟机A：添加允许的协议
]# firewall-cmd    --zone=public  --add-service=ftp
]# firewall-cmd   --zone=public  --list-all
虚拟机B
]# curl   http://192.168.88.240    #成功
]# curl   ftp://192.168.88.240    #成功
```


### 12.3 防火墙public区域添加规则（永久）

```
-永久（--permanent  破门能它） 
]# firewall-cmd   --reload    #加载防火墙永久策略
]# firewall-cmd   --zone=public    --list-all

]# firewall-cmd    --permanent                                    --zone=public   --add-service=http   #永久添加http协议
]# firewall-cmd   --permanent                                    --zone=public     --add-service=ftp    #永久添加ftp协议

]# firewall-cmd   --reload    #加载防火墙永久策略
]# firewall-cmd   --zone=public   --list-all
```

### 12.4 防火墙单独拒绝PC2所有的访问

```
虚拟机A：   
[root@server ~]# firewall-cmd  --zone=block            --add-source=192.168.88.2

虚拟机A：删除策略
[root@server ~]# firewall-cmd --zone=block            --remove-source=192.168.88.2
```

### 12.5 卸载防火墙软件

```
[root@server ~]# yum  -y remove  firewalld
```

---

## 13. 服务管理

* **方法一：手动进行运行**       
    * 运行: /usr/sbin/httpd       
    * 停止: killall  httpd
    
* **方法二：采用systemd方式运行**

```
systemctl  restart      服务名    #重起服务   
systemctl   start       服务名      #开启服务 
systemctl   stop        服务名      #停止服务
systemctl   status      服务名      #查看服务当前的状态
systemctl  enable       服务名     #设置服务开机自启动
systemctl   disable     服务名      #设置服务禁止开机自启动
systemctl   is-enabled  服务名    #查看服务是否开机自启
```

---
