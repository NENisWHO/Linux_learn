# 10_1 Linunx Web服务管理

[toc]

---

## 1. 环境准备
1. **所有的虚拟机设置SELinux运行模式**

```
[root@server ~]# getenforce
Enforcing
[root@server ~]# setenforce 0
[root@server ~]# getenforce
Permissive
[root@server ~]# vim   /etc/selinux/config
SELINUX=permissive
```
2. **所有虚拟机卸载防火墙**

```
[root@server ~]# yum  -y  remove  firewalld
[root@server ~]# rpm   -q  firewalld
```

---

## 2. Web服务

### 2.1 Web服务简介

1. **基于 B/S （Browser/Server）架构的网页服务**
    * 服务端提供网页
    * 浏览器下载并显示网页
2. **Wed服务用到的协议**
    * Hyper Text Markup Language，（**HTML**）超文本标记语言
    * Hyper Text Transfer  Protocol，（**HTTP**）超文本传输协议
    
3. **配置Wed服务的步骤**
    * 三步走：**装包、配置、启服务**
    
4. 实现Web功能的软件
    * httpd、Nginx、Tomcat
        * httpd由软件基金会**Apache**
        
--- 

## 2.2 Web配置

### 2.2.1 提供的默认配置
    * Listen：监听地址:端口（80）
    * ServerName：本站点注册的DNS名称（空缺）
    * DocumentRoot：**网页根目录（/var/www/html）**
    * DirectoryIndex：**起始页/首页文件名（index.html）**
    
### 2.2.2 Web服务的主配置文件
    * **/etc/httpd/conf/httpd.conf **
    * 因配置**/etc/httpd/conf/httpd.conf**此文件导致web访问失败可能出现的错误有：

```shell
[root@server ~]# systemctl  restart httpd
Job for httpd.service failed because the control process exited with error code. See "systemctl status httpd.service" and "journalctl -xe" for details.

[root@server ~]# journalctl   -xe        #查错  
```
    
### 2.2.3 /etc/httpd/conf/httpd.conf 文件反映出来的”访问控制信息“

```
1. 
    当子目录没有规则，默认继承上一级目录规则
    针对此目录有单独配置，则不继承上一级目录规则
    <Directory       />          
        Require  all  denied     #拒绝所有人访问
    </Directory>    
    
    <Directory    "/var/www">
        Require all granted      #允许所有人访问
    </Directory>
    总结：默认情况下网页文件，必须在/var/www目录下，才能允许访问
    
2. 将默认DocumentRoot修改为自己的
    虚拟机A：                                                   
    ]#mkdir    /webroot
    ]#echo  wo   shi   webroot    >   /webroot/index.html
    ]# vim    /etc/httpd/conf/httpd.conf
    …….此处省略一万字
    DocumentRoot    "/webroot"
    <Directory     "/webroot"> #针对于/webroot路径
        Require  all  granted   #允许所有人访问
    </Directory>
    …….此处省略一万字
    ]# systemctl    restart   httpd     #重启服务
    ]# curl   192.168.88.240       
    wo shi webroot
```

* <mark>**注意:** **<font color=red>DocumentRoot只有一个是生效的，下面的会覆盖上面的所以下面的生效</font>**</mark>

### 2.2.4 修改监听端口，访问

* **<font color=red>主配置文件：/etc/httpd/conf/httpd.conf</font>**
* **<font color=red>调用配置文件：/etc/httpd/conf.d/\*.conf</font>**
* **注意：在”调用配置文件“里添加了DocumentRoot路径后”主配置文件的DocumentRoot“路径被覆盖**

```
1. 端口:数字编号起到标识作用，标识协议或者进程
   http协议默认端口：80
   
[root@server ~]# vim  /etc/httpd/conf.d/haha.conf
DocumentRoot    /var/www/cbd
Listen  8000
[root@server ~]# systemctl   restart httpd
[root@server ~]# curl  192.168.88.240:8000
[root@server ~]# curl  192.168.88.240     #默认是80端口
```


### 2.2.5 访问Web服务的流程

1. DocumentRoot 为自己修改的路径/webroot
**客户端curl  192.168.88.240**---->**http协议方式**------>**服务端 192.168.88.240**--->**响应http协议请求**----->**httpd进程**----->**主配置文件设置**---->**DocumentRoot  /webroot**--->**index.html**

    * <mark>**注意：所有现有页面都叫<font color=red>index.html</font>，不要修改/etc/httpd/conf/httpd.conf 下的 ”DirectoryIndex index.html“**</mark>


2. 网络路径与实际路径

```
网络路径: curl  192.168.88.240
实际路径: /webroot

DocumentRoot  /webroot
网络路径: curl  192.168.88.240/abc
实际路径: /webroot/abc

DocumentRoot  /webroot
网络路径: curl  192.168.88.240/abc/cbd
实际路径: /webroot/abc/cbd
```

## 2.3 Web访问出现测试界面的可能
1. 没有网页文件
2. 网页文件名称不是index.html
3. httpd的访问控制规则拒绝
4. SELinux的没有关闭

## 2.4 虚拟web主机

### 2.4.1 多页面的实现
* **/etc/httpd/conf/httpd.conf提供的DocumnetRoot是一个页面，要想实现多个页面就要使用虚拟Web主机**

### 2.4.2 虚拟Web主机
* 由同一台服务器,提供多个不同的Web站点
    
### 2.4.3 区分方式
* 基于**域名**的虚拟主机
* 基于**端口**的虚拟主机
* 基于**IP地址**的虚拟主机
    
### 2.4.4 在”调用配置文件“里增加配置

1. **域名**

```
1. 为每个虚拟站点添加配置   
<VirtualHost    IP地址:端口>
       ServerName   此站点的DNS名称
       DocumentRoot  此站点的网页根目录
</VirtualHost>

2. 示例
（1）虚拟机A：   
    [root@server ~]# vim  /etc/httpd/conf.d/xixi.conf
    <VirtualHost     *:80>   #在所有IP地址监听80
    ServerName    www.qq.com   #网站的域名
    DocumentRoot    /var/www/qq  #网页文件路径
    </VirtualHost>        

    <VirtualHost    *:80>       
    ServerName     www.lol.com
    DocumentRoot    /var/www/lol
    </VirtualHost>
    
    ]#mkdir     /var/www/qq     /var/www/lol
    ]#echo  wo shi QQ   >  /var/www/qq/index.html
    ]#echo  wo shi LOL  >  /var/www/lol/index.html
    ]#systemctl    restart     httpd

（2）采用/etc/hosts文件直接解析域名，只为本机解析
    ]# vim     /etc/hosts  
    …….此处省略一万字
    192.168.88.240   www.qq.com    www.lol.com
    ]# curl   www.qq.com
    ]# curl   www.lol.com
```

2. **端口**

```
[root@server ~]#vim  /etc/httpd/conf.d/xixi.conf
<VirtualHost   *:80>
   ServerName  www.qq.com
   DocumentRoot   /var/www/qq
</VirtualHost>
Listen  8080
<VirtualHost   *:8080>
   ServerName   www.qq.com
   DocumentRoot    /var/www/lol
</VirtualHost>
[root@server ~]# systemctl restart httpd
[root@server ~]# curl  www.qq.com:8080
[root@server ~]# curl  www.qq.com
```

---



