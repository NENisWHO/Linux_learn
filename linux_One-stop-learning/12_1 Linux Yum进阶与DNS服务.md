# 12_1 Linux Yum进阶与DNS服务

[toc]

---

## 1. Yum进阶

### 1.1 自定义yum仓库

1. 自定义yum仓库：**将自己下载的RPM包，构建为Yum仓库**
    * 完整的yum仓库：**1.众多的软件包；2.仓库数据文件（仓库清单）**

2. 示例：由真机将tools.tar.gz传递到虚拟机A的/root目录下

```
1. 建立自定义yum仓库
[root@server ~]# ls     /root
[root@server ~]# tar -tf    /root/tools.tar.gz 

[root@server ~]# tar  -xf    /root/tools.tar.gz   -C   /
[root@server ~]# ls     /
[root@server ~]# ls    /tools/        
[root@server ~]# ls    /tools/other/

[root@server ~]#createrepo   /tools/other #生成仓库数据文件
[root@server ~]# ls    /tools/other/ 

[root@server ~]# vim    /etc/yum.repos.d/mydvd.repo 
……此处省略一万字
[myrpm]                #唯一标识 
baseurl=file:///tools/other   #指定Yum仓库的路径
gpgcheck=0                                        
[root@server ~]# yum   repolist         
[root@server ~]# yum  -y  install  sl
[root@server ~]# yum  -y  install  cmatrix

2. 当仓库文件有变化时，更新自定义的yum仓库
    * 仓库数据文件的更新
    * Yum仓库缓存的更新
    
]# mv  /tools/other/sl-5.02-1.el7.x86_64.rpm   /root
]# ls  /tools/other/
]# createrepo  --update  /tools/other #更新仓库数据文件
]# yum   repolist
]# yum  makecache   #更新缓存数据
]# yum   repolist
```

### 1.2 网络Yum仓库

* 网络Yum仓库：
    * 虚拟机A：提供仓库内容（**构建网络服务**，提供仓库内容）
    * 虚拟机B：进行访问仓库内容
    * 原理流程图：**虚拟机B运行yum---->仓库配置文件---->访问虚拟机A的ftp服务提供仓库内容**
    
```
一、虚拟机A：提供仓库内容（FTP服务） 
    1.构建FTP服务                 
    [root@server ~]# yum  -y   install   vsftpd
    [root@server ~]# systemctl  restart  vsftpd  #重启服务
    [root@server ~]# systemctl  enable   vsftpd  #设置开机自启

    2.通过FTP提供仓库内容
    [root@server ~]# cp  -r   /tools/other    /var/ftp
    
二、虚拟机B：进行访问仓库内容   
    [root@pc2 ~]# vim  /etc/yum.repos.d/mydvd.repo
    ……此处省略一万字
    [haha]
    baseurl=ftp://192.168.88.240/other
    gpgcheck=0
    [root@pc2 ~]# yum  clean  all    #清空Yum的缓存
    [root@pc2 ~]# yum  repolist   
    
三、虚拟机A：提供仓库内容（FTP服务）   
    [root@server ~]# mkdir    /var/ftp/dvd
    [root@server ~]# mount   /dev/cdrom    /var/ftp/dvd
    [root@server ~]# curl    ftp://192.168.88.240/dvd/
    [root@server /]# vim   /etc/fstab     #修改配置
    /dev/cdrom   /var/ftp/dvd   iso9660   defaults  0  0
    [root@server /]# umount    /var/ftp/dvd
    [root@server /]# ls     /var/ftp/dvd
    [root@server /]# mount    -a
    mount: /dev/sr0 写保护，将以只读方式挂载
    [root@server /]# ls    /var/ftp/dvd
    CentOS_BuildTag  images    repodata
    ........
    [root@server /]# vim   /etc/yum.repos.d/mydvd.repo
    [centos]
    baseurl=ftp://192.168.88.240/dvd
    gpgcheck=0
    [myrpm]
    baseurl=ftp://192.168.88.240/other
    gpgcheck=0
    [root@server ~]# yum  clean  all    #清空Yum的缓存
    [root@server ~]# yum  repolist 


四、虚拟机B：进行访问仓库内容   
    [root@pc2 ~]# vim   /etc/yum.repos.d/mydvd.repo
    ……此处省略一万字
    [centos]
    baseurl=ftp://192.168.88.240/dvd
    gpgcheck=0
    [root@pc2 ~]# yum  clean  all    #清空Yum的缓存
    [root@pc2 ~]# yum  repolist 

```


## 2. DNS服务

### 2.1 为什么要使用DNS系统
* 问什么要使用DNS系统：**通过域名方便访问ip地址的主机**

### 2.2 DNS服务器的功能
* DNS服务器的功能：
    * 正向解析：根据注册的域名查找其对应的IP地址
    * 反向解析：根据IP地址查找对应的注册域名，**不常用**
    
### 2.3 DNS服务器分类
* DNS服务器分类：
    * 根域名服务器：”.“
    * 一级DNS服务器：”.cn      .us     .tw   .hk     .jp     .kr“
    * 二级DNS服务器：”.com.cn    .org.cn   .net.cn“
    * 三级DNS服务器：”haha.com.cn    xixi.com.cn    .nb.com.cn“
    
* 完全合格的域名：**<font color=red>站点名+注册的域名</font>**
    * 如：www.qq.com、mail.qq.com
    
### 2.4 DNS服务使用的软件及配置
* DNS服务要用到**BIND程序**
    * BIND（Berkeley Internet Name Daemon）：**伯克利 Internet 域名服务**
    * BIND服务器端程序：**<font color=red>bind（主程序）、bind-chroot（提供牢笼政策）</font>**

        * 主要执行程序：**/usr/sbin/named**
        * 系统服务：**named**           
        * DNS协议默认端口：**TCP/UDP、53端口**
        * 运行时的虚拟根环境：**/var/named/chroot**
        * 主配置文件：**/etc/named.conf** ；#设置负责解析的域名 
        * 地址库文件：**/var/named**；#完全合格的域名与IP地址对应关系

* **<mark><font color=red>注意：DNS是唯一一个可以删除配置的服务(/etc/named.conf)</font></mark>**

### 2.5 搭建DNS服务示例

1. 解析

```
1. 
zone "." IN {        
        type hint;         #根域名是hint类型，master为主，slave为副
        file "named.ca";    #地址库文件的名字叫named.ca
};

2. 地址库文件名字tedu.cn.zone
         NS     server                 
server   A      192.168.88.240    #server解析后的结果为192.168.88.240
www      A      1.1.1.1
ftp      A      2.2.2.2        #DNS服务器的功能是指引一个位置，访问对不对不归DNS管

* NS：nameseaver
* A:address

**！！补全之后的地址库文件tedu.cn.zone!!**
tedu.cn          NS     server.tedu.cn                
server.tedu.cn   A      192.168.88.240    
www.tedu.cn      A      1.1.1.1
ftp.tedu.cn      A      2.2.2.2        
```
2. 示例

```
一、虚拟机A：构建DNS服务器    
1.安装软件包
    [root@server ~]# yum  -y  install   bind    bind-chroot

2.修改主配置文件      
    [root@server ~]# cp -p /etc/named.conf  /root #备份数据
    [root@server ~]# ls  -l    /root/named.conf

    [root@server ~]# vim   /etc/named.conf
    options  {                  
        directory     "/var/named";   #定义地址库文件存放路径
    };
    zone "tedu.cn"  IN {       #定义负责的解析tedu.cn域名
        type  master;        #权威主DNS服务器
        file   "tedu.cn.zone";     #地址库文件名称
    };

3.建立地址库文件   
    * 保证named用户对地址库文件有读取权限
    * 如果没有以点作为结尾，那么默认补全本地库文件负责的域名
    ]# cd    /var/named/
    ]# cp  -p  named.localhost  tedu.cn.zone   #保持权限不变
    ]# ls   -l   tedu.cn.zone
    ]# vim     tedu.cn.zone 
    ……此处省略一万字
                NS    server      #声明DNS服务器为  server
    server      A      192.168.88.240    #server解析结果为192.168.88.240
    www         A      1.1.1.1
    ftp         A      2.2.2.2
    [root@server named]# systemctl   restart    named
        
二、虚拟机B：测试DNS服务器
1.指定DNS服务器地址
    ]# echo nameserver  192.168.88.240  >  /etc/resolv.conf
    ]# cat  /etc/resolv.conf
2.命令测试域名解析
    ]# nslookup    www.tedu.cn  
    ]# host    ftp.tedu.cn  
    
!! nslookup会先找/etc/resolv.conf文件如果找不到，会自己给自己做尝试 ！！ 

/etc/hosts文件与/etc/resolv.conf文件
1./etc/hosts文件域名解析最高优先级
2./etc/resolv.conf文件指定DNS服务器地址
```

### 2.6 DNS特殊解析

1. DNS泛域名解析

```
虚拟机A：
[root@server /]# vim   /var/named/tedu.cn.zone
……此处省略一万字
             NS    server                 
server       A      192.168.88.240
www          A      1.1.1.1
ftp          A      2.2.2.2
*            A      6.6.6.6    # 任意站点名，注意是站点名
tedu.cn.     A      7.7.7.7    # 域名解析
vip          CNAME    ftp      #vip解析结果与ftp解析结果一致
[root@server /]# systemctl   restart    named
虚拟机B测试：
[root@pc2 /]#  nslookup    wwwwww.tedu.cn
[root@pc2 /]#  nslookup     tedu.cn
```

---






