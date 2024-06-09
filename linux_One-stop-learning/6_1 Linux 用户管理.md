# 6_1 Linux 用户管理

[toc]

---

## 1. 用户管理
* 用户管理的作用：可以登入操作系统；不同的用户有不同的权限
* 唯一标识：UID（0~60000[默认最大为60000]）
    * 管理员root的UID：永远为0
    * 普通用户的UID：默认从1000开始

---    

## 2. 组账户
* 组账户作用: 方便管理用户    
* 唯一标识：GID（编号从0开始的编号，默认最大60000）
* 原则：Linux一个用户必须至少属于一个组
* 组账户的分类：
    * 基本组：系统创建与用户同名    
    * 附加组（从属组）：由管理员创建，由管理员进行加入

---    

## 3. 本地账户数据文件
* **/etc/passwd: 用户基本信息配置文件**
* **/etc/shadow: 用户密码信息配置文件**
* **/etc/group: 组基本信息配置文件**
* **/etc/gshadow: 组管理信息配置文件**

```shell
[root@localhost ~]# head -1  /etc/passwd   #显示文件第一行
root:x:0:0:root:/root:/bin/bash
test:x:1000:1000:test:/home/test:/bin/bash
用户名:密码占位符:UID:基本组GID:用户描述信息:家目录:解释器
```
---

## 4. 用户账号创建与删除

1. **命令useradd**
    * 格式：useradd [选项] 用户名
    * 常用命令选项：
        * -u：指定 用户UID
        * -d：指定宿主目录（家目录），默认为/home/用户名
        * -G：指定所属的附加组
        * -s：指定用户登录解释器（**/sbin/nologin**：禁止用户登入操作系统的解释器）
        
2. **命令usermod**
    * 格式：usermod  [选项] 用户名
    * 常用命令选项：
        * -l：更改用户帐号的登录名称
        * -u：用户id
        * -d：家目录路径    
        * -s：登录解释器
        * -G：附加组     #重置附加组
        
3. **命令userdel**
    * 格式：uesrdel [-r] 用户名
        * -r：家目录/用户邮件也一并删除

---
        
## 5. 设置密码
* **命令passwd**
    * 格式：passwd [选项] 用户名
    * 非交互式设置密码：echo  ***   |   passwd  --stdin  用户名
        * --stdin：从标准输入（如管道）取密码

```
[root@localhost ~]# grep test /etc/shadow
test:$6$GBcYj1Bp10i/6bXf$ehiXjzRcIV9VmGTcBj/PQJKLQj9x4ee6Q/dkXNGo/D2w1r6E9sBQgjVH/Tz3qe1GIycAzK.nvBF8MU7YLh/XV/::0:99999:7:::

字段1：用户帐号的名称
字段2：加密后的密码字符串
字段3：上次修改密码的时间
字段4：密码的最短有效天数，默认0
字段5：密码的最长有效天数，默认99999
字段6：密码过期前的警告天数，默认7
字段7：密码过期后多少天禁用此用户账号
字段8：帐号失效时间，默认值为空
字段9：保留字段（未使用）
```
---

## 6. 用户初始配置文件

* root用户的初始配置文件：/root/.bashrc
* 全局初始配置文件：/etc/bashrc

---

## 7. 组账户管理

```shell
# /etc/group，保存组帐号的基本信息
# 每个组记录一行，以：分割为4个字段
[root@localhost ~]# grep test /etc/group
test:x:1000:test
# 组名:组密码占位符:组的GID:组成员列表
```

* **命令groupadd**：添加组
* **命令gpasswd**
    * 格式：gpasswd [选项] 组名
    * 常用命令选项
        * -a：添加组成员，每次只能加一个
        * -d：删除组成员，每次只能删一个
        * -M：定义（重置）组成员用户列表，可设置多个
        * -A：定义组管理员列表

---

## 8. 总结

```
1. 用户与组重要的配置文件     
    /etc/passwd:用户基本信息配置文件
    /etc/shadow:用户密码信息配置文件  
    /etc/group:组基本信息配置文件
    /etc/gshadow:组管理信息配置文件

2. Linux系统执行useradd命令，会完成那些操作？
    会在/etc/passwd增加一行信息
    会在/etc/shadow增加一行信息
    会在/home新增用户家目录
    会在/var/spool/mail增加用户邮件文件
    会在/etc/group增加一行组信息
    会在/etc/gshadow增加一行组的管理信息

3. Linux系统执行userdel -r命令，会完成那些操作？
    会在/etc/passwd删除一行信息
    会在/etc/shadow删除一行信息
    会在/home删除用户家目录
    会在/var/spool/mail删除用户邮件文件
    会在/etc/group删除一行组信息
    会在/etc/gshadow删除一行组的管理信息
```
---






