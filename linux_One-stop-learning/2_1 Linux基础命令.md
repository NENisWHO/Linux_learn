# 2_1 Linux基础命令

[TOC]

## 装机后的一些小命令查看系统的信息

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

