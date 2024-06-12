# 11_1 Linux NFS服务与触发挂载服务

[toc]

---

>**文件共享服务：scp、FTP、web（httpd）、NFS**

## 1. NFS服务基础

* Network File System，**网络文件系统**
    * 用途：**为客户机提供共享使用的文件夹**
    * 协议：NFS（ 2049）、RPC（ 111）
    * 所需软件包：**nfs-utils**
    * 系统服务：**nfs-server**

    
### 1.1 示例

```
1. 虚拟机A：服务端              
    [root@server ~]# rpm  -q  nfs-utils
    nfs-utils-1.3.0-0.54.el7.x86_64
    [root@server ~]# mkdir   /abc  #创建共享目录
    [root@server ~]# echo  haha  >  /abc/h.txt
    [root@server ~]# echo  xixi  >  /abc/x.txt
    [root@server ~]# ls  /abc/
    [root@server ~]# vim   /etc/exports
    文件夹路径      客户机地址(权限)  
    /abc       *(ro)       #允许所有客户端进行只读访问
    [root@server ~]# systemctl   restart   nfs-server

2. 虚拟机B：客户端        
    ]#rpm  -q  nfs-utils
    nfs-utils-1.3.0-0.54.el7.x86_64
    ]#showmount -e 192.168.88.240 #查看对方nfs共享
    Export list for 192.168.88.240:
    /abc   *
    ]# mkdir    /mnt/mynfs
    ]# mount    192.168.88.240:/abc    /mnt/mynfs
    ]# ls     /mnt/mynfs
    ]# df -h   /mnt/mynfs   #查看正在挂载的设备信息

3. 实现开机自动挂载           
_netdev：声明网络设备，系统在具备网络参数后，再进行挂载本设备
    [root@pc2 ~]# vim    /etc/fstab   
    ……此处省略一万字
    192.168.88.240:/abc   /mnt/mynfs    nfs     _netdev    0    0
    [root@pc2 ~]# umount   /mnt/mynfs
    [root@pc2 ~]# ls   /mnt/mynfs
    [root@pc2 ~]# mount   -a
    [root@pc2 ~]# ls   /mnt/mynfs
```

---

## 2. 触发挂载autofs

### 2.1 触发挂载基础

1. **由 autofs 服务提供的“按需访问”机制**
    * 只要访问挂载点就会触发响应，自动挂载指定设备
    * 闲置一段时间后，会自动卸载

```
[root@pc2 ~]# yum  -y  install  autofs
[root@pc2 ~]# systemctl restart autofs
[root@pc2 ~]# ls  /misc        # 访问啥也没有
[root@pc2 ~]# ls  /misc/cd     # 访问/misc/cd就将光驱设备挂上了
```

2. **触发挂载实现，必须多级的目录结构： /监控目录/挂载点目录**      

    * 主配置文件/etc/auto.master
        * 监控点目录  	挂载配置文件的路径
    * 挂载配置文件，比如 /etc/auto.misc
        * 触发点子目录  	  -挂载参数    		:设备名
        
3. 案例：虚拟机B访问/myauto/nsd,光驱设备挂载/ myauto/nsd

```
[root@pc2 ~]# yum -y  install   autofs
[root@pc2 ~]# vim   /etc/auto.master
……此处省略一万字 
/myauto      /opt/xixi.txt
……此处省略一万字
[root@pc2 ~]# vim  /opt/xixi.txt
nsd    -fstype=iso9660     :/dev/cdrom
[root@pc2 ~]# systemctl  restart   autofs
[root@pc2 ~]# ls   /myauto/
[root@pc2 ~]# ls   /myauto/nsd
```

### 2.2 触发挂载进阶autofs与NFS

* **任务：虚拟机B访问/myauto/abc,虚拟机A 的nfs共享/public挂载到/myauto/abc**

```
[root@pc2 ~]# yum -y install autofs
[root@pc2 ~]# vim   /etc/auto.master
……此处省略一万字 
/myauto      /opt/xixi.txt    
……此处省略一万字                          
[root@pc2 ~]# vim   /opt/xixi.txt
nsd    -fstype=iso9660     :/dev/cdrom
test  -fstype=nfs    192.168.88.240:/abc
[root@pc2 ~]# systemctl  restart  autofs
[root@pc2 ~]# ls  /myauto/abc
```

---












