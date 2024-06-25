# 4_1 Linux Centos7的RPM相关知识

[toc]

>系统环境centos7.9
>临时挂载光盘文件：mount  /dev/cdrom /dvd

---

## 1. RPM包文件名特征
```
* 软件名-版本信息.操作系统.硬件架构.rpm
* firefox-52.7.0-1.el7.centos.x86_64.rpm
* 软件名：firefox
* 版本信息：52.7.0-1.el7
* 操作系统：centos
* 硬件架构：x86_64
```
---

## 2. RPM软件包管理

```
[root@localhost ~]# ls /dvd
CentOS_BuildTag  EULA  images    LiveOS    repodata              RPM-GPG-KEY-CentOS-Testing-7
EFI              GPL   isolinux  Packages  RPM-GPG-KEY-CentOS-7  TRANS.TBL
```

|   封包类型   |                       说明                        |
| :---------: | :-----------------------------------------------: |
|  rpm软件包   |               .rpm，适用于RetHat系列               |
|  deb软件包   |               .deb，适用于Debian系列               |
| 源代码软件包 | .tar.gz、.tar.bz2 压缩包提供，包含程序的原始代码文件 |
|     其他     |         install.sh、setup、\*.bin、\*.pl等         |

---

## 3. RPM包的一般安装位置

|             文件类别             |             默认安装位置             |
| :------------------------------: | :--------------------------------: |
|     普通执行<mark>程序</mark>     |         /usr/bin  or  /bin         |
| 服务器<mark>程序</mark>、管理工具 |        /usr/sbin  or  /sbin        |
|             配置文件             |        /etc  or  /etc/软件名        |
|             日志文件             |   /var/log/  or  /var/log/软件名/   |
|        程序文档、man手册页        | /usr/share/doc  or  /usr/share/man |

---

## 4. RPM基本命令

|                     命令参数                      |                  作用                   |
| :----------------------------------------------: | :-------------------------------------: |
|                     rpm -qa                      |      当前系统中的所有已经安装的软包       |
|                  rpm -q 软件包名                  |            查看是否安装了软件            |
|                 rpm -qi 软件包名                  |               查询软件信息               |
|                 rpm -ql 软件包名                  | 查看这个软件在安装时将文件放在了那些目录下 |
|                rpm -qf [文件路径]                 |    查询某个目录/文件是哪个RPM包带来的     |
|           rpm -qpl rpm包(run目录下的包)           |      还没安装，查询软件包的安装清单       |
|                  pm -qpi rpm包                   |        还没安装，显示软件包的信息         |
| rpm --import 光盘挂载目录下的RPM-GPG-KEY-CentOS-7 |               导入红帽签名               |
|               rpm -ivh    软件包名                |                安装软件                 |
|                rpm -evh   软件包名                |                卸载软件                 |

**<font color=red>注意：</font>**
* **rpm -qpl rpm包(run目录下的包) 这条命令可能会报错：**
    * **<mark>要导入rpm签名 rpm --import /dvd/RPM-GPG-KEY-CentOS-7</mark>**

---    

## 5. yum

1. **rpm命令无法解决依赖关系，yum可以解决依赖关系**
    * yum（yellowdog updater modified）
      * 基于RPM包构建的软件更新机制
      * 自动解决软件包依赖关系
      * 所有软件包由集中的YUM软件仓库提供  
    </br>
    * 仓库清单：/dvd/repodata
    * yum工作流程
        *  **yum-->读取/etc/yum.repos.d/\*.repod配置文件内容-->baseurl=file:///dvd从而找到仓库的具体位置**
    * 查看仓库信息：yum repolist -v  、
    * 查询仓库是否有软件包：yum list 软件包名
    * 清空yum缓存：yum clean all
    * yum安装：      yum install 软件名 （-y 不用再询问，我默认yes）
    * yum卸载：      yum remove 软件名 （-y，不用再询问，我默认yes）
   
```shell
# 自建yum仓库
# vim /etc/yum.repos.d/test.repo
[]                 #名字--仓库标识
name=              #仓库描述信息
baseurl=           #仓库位置url
enable=            #能不能用 1可用，0不可用
gpgcheck=          #是否检查红帽签名 1检查，0不检查
gpgkey=            #仓库的签名文件路径

# 永久挂载本地yum仓库
# vim /etc/fstab
#
# /etc/fstab
# Created by anaconda on Sun Jun  9 16:59:35 2024
#
# Accessible filesystems, by reference, are maintained under '/dev/disk'
# See man pages fstab(5), findfs(8), mount(8) and/or blkid(8) for more info
#
/dev/mapper/centos-root /                       xfs     defaults        0 0
UUID=4dac65fa-8c23-4f6e-8b9d-dbc8baf50440 /boot                   xfs     defaults        0 0
/dev/mapper/centos-swap swap                    swap    defaults        0 0

/dev/cdrom /dvd iso9660 defaults 0 0  #添加这一条即可开机自动挂载
```
2. 本地yum仓库排错
    * **没有挂载光驱设备**
    * **/etc/yum.repos.d 目录下的配置文件内容**
    * **/etc/yum.repos.d 目录下，错误的配置文件影响**
   
3. 搭建本地yum

```shell
# 1. 挂载光盘
1. mkdir /mydvd
2. mount /dev/cdrom /mydvd
3. ls /mydvd
# 2. 改yum配置文件
1. cd /etc/yum.repos.d
2. mkdir /etc/yum.repos.d/bak
3. mv /etc/yum.repos.d/*.repo /etc/4. yum.repos.d/bak
4. vim /etc/yum.repos.d/mydvd.repo
    [mydvd]
    name=mydvd
    baseurl=file:///mydvd
    enabled=1
    gpgcheck=0 
    
5. yum repolist
# 3. 开机永久挂载
1. vim /etc/fstab
    ......
    /dev/cdrom /mydvd iso9660 defaults 0 0
    ......
    
2. umount /mydvd
3. mount -a 
4. yum repolist
5. yum clean all
6. yum repolist
    
```
---