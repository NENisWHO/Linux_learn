# 13_1 Linux 邮件服务与NTP时间服务

[toc]

---


## 1. 邮件服务器
* 邮件服务器的作用：
    * 为用户提供电子邮箱存储空间（用户名@邮件域名）
    * 处理用户发出的邮件 —— 传递给收件服务器
    * 处理用户收到的邮件 —— 投递到邮箱

* 示例

```
[root@server /]# rpm  -q  postfix  #提供邮件功能的软件
postfix-2.10.1-9.el7.x86_64
[root@server /]# systemctl status postfix 
[root@server /]# useradd   yg
[root@server /]# useradd   xln


* mail 发信操作: mail   -s   '邮件标题'  -r  发件人 收件人 
[root@server /]# yum  -y   install  mailx  #提供mail命令软件
[root@server /]# mail   -s  'test01'   -r   yg    xln
hahaxixiehehelele
.                #一行只有一个点表示提交   
EOT   

* mail 收信操作: mail    [-u  用户名]
[root@server /]# mail   -u    xln
>N  1  yg@server.tedu.cn    Fri Sep 18 17:24  18/510
&  1            #输入邮件编号
&  quit       #退出       
  
* 非交互式发邮件：          
]# echo 123456  |  mail  -s  'test02'   -r   yg  xln
]# mail  -u  xln  
```

---

## 2. NTP时间服务器

* **时间服务器的作用：提供标准时间**
    * Network Time Protocol（网络时间协议）
    * 它用来同步网络中各个计算机的时间的协议
    * 210.72.145.39 (国家授时中心服务器IP地址)
    * Stratum（分层设计）    
    * Stratum层的总数限制在15以内（包括15）
    
```
一、虚拟机A：时间服务器    
1.安装软件包chrony
    [root@server /]# yum  -y  install   chrony
    [root@server /]# rpm  -q  chrony
2.修改配置文件
    [root@server /]# vim  /etc/chrony.conf      
    #server   0.centos.pool.ntp.org   iburst #与谁同步时间
    #server   1.centos.pool.ntp.org   iburst #iburst表示快速同步
    #server   2.centos.pool.ntp.org   iburst
    #server   3.centos.pool.ntp.org   iburst
    26行  allow   all    #开头的#去掉，修改为允许所有客户端
    29行  local  stratum  10   #开头的#去掉，本机为第10层的时间服务器
3.重启时间服务
    [root@server /]# systemctl    restart    chronyd


二、虚拟机B：客户端           
1.安装软件包chrony
    [root@pc2 /]# yum  -y  install   chrony
2.修改配置文件
    [root@pc2 /]# vim   /etc/chrony.conf      
    #server  0.centos.pool.ntp.org  iburst  #iburst表示快速同步
    #server  1.centos.pool.ntp.org  iburst
    #server  2.centos.pool.ntp.org  iburst
    server  192.168.88.240   iburst   #与192.168.88.240同步时间
3.重启时间服务
    [root@pc2 /]# systemctl   restart   chronyd

4.测试：  
    [root@pc2 /]# date   -s   "2008-1-1"      
    [root@pc2 /]# date
    [root@pc2 /]# systemctl   restart   chronyd 
    [root@pc2 /]# date
    [root@pc2 /]# date
```

---