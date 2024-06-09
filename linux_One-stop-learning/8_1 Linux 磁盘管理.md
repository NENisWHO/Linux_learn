# 8_1 Linux 磁盘管理

[toc]

---

## 1. 磁盘管理基础

1. **命令lsblk**
    * 列出当前系统识别的硬盘

2. **扇区**
    * **是磁盘中最小的物理存储单位。通常情况下每个扇区的大小是512字节。**

3. VM、KVM虚拟机磁盘识别标识
* VM：
    * /dev/sd[a,b,c]
    * 光盘：/dev/sr0
* KVM:
    * /dev/vd[a,b,c]

---    

## 2. 虚拟机新加一块硬盘经历的步骤
```mermaid
flowchart LR
	识别硬盘-->分区规划-->格式化-->挂载使用; 
```

### 2.1 识别硬盘
* 自动识别 **lsblk命令**，会列出当前系统识别的硬盘

### 2.2 分区规划（MBR、GPT）
>分区方案：**MBR**与**GPT**
#### 2.2.1 MBR（msdos）分区模式
* 分区类型：主分区、扩展分区(占用所有剩余空间)、逻辑分区
* **最多**只能有**4个主分区**
* **扩展分区可以没有，至多有一个**
* 1~4个主分区，或者 3个主分区+1个扩展分区（n个逻辑分区）
* 最大支持容量为 **2.2TB** 的磁盘
* **扩展分区不能格式化，空间不能直接存储数据**
* 可以用于存储数据的分区：主分区与逻辑分区
* **分了4个主分区但还有空间未分配，剩余的空间将不可使用**

```
fdisk常用交互指令：专门用来划分MBR分区方案
    m 列出指令帮助
    p 查看现有的分区表（存放分区信息的表格）
    n 新建分区
    d 删除分区
    q 放弃更改并退出
    w 保存更改并退出
```
#### 2.2.2 GPT分区模式
* GPT，GUID Partition Table
* 全局唯一标识分区表
* 突破固定大小64字节的分区表限制
* 最多可支持128个主分区，最大支持18EB容量 

```
1. parted常用分区指令
    –help    //查看指令帮助
    –mktable  gpt    //建立指定模式分区表
    –mkpart  分区的名称  文件系统类型  start  end
       //指定大小或百分比%作为起始、结束位置
    –print   //查看分区表
    –rm  序号    //删除指定的分区
    –quit   //退出交互环境
    

2. parted进行分区                                   
[root@localhost ~]# parted      /dev/sdd    
(parted) mktable   gpt      #指定分区模式
(parted) mkpart                #划分新的分区 
分区名称？ []? haha             #随意写，不写也可以
文件系统类型？ [ext2]? ext4    #随意写，不会进行格式化
起始点？ 0 
结束点？ 5G 
忽略/Ignore/放弃/Cancel? Ignore #选择忽略，输入i(tab)补全
(parted) print                 #查看分区表信息
(parted) unit   GB             #使用GB作为单位
(parted) print 
(parted) mkpart              #划分新的分区
分区名称？ []? haha 
文件系统类型？ [ext2]? ext4 
起始点？ 5G                    #为上一个分区的结束
结束点？ 100%                 #全部空间
(parted) print                      
(parted) quit              #退出
[root@localhost ~]# lsblk 
[root@localhost ~]# mkfs.xfs    /dev/sdd1     #格式化文件系统
[root@localhost ~]# blkid    /dev/sdd1     
[root@localhost ~]# vim  /etc/fstab    #增加一行信息
/dev/sdd1    /mypart3    xfs    defaults  0   0
[root@localhost ~]# mkdir   /mypart3
[root@localhost ~]# mount   -a
[root@localhost ~]#  df  -h   /mypart3
```

### 2.3 格式化
>格式化：赋予空间**文件系统**的过程
>文件系统：数据在空间中，存放的**规则**
>windows常见的文件系统：NTFS    FAT(兼容性强)
>Linux常见的文件系统：**<font color=red>ext4（RHEL6）、xfs（RHEL7）</font>**、FAT

```
mkfs.(tab)(tab)             #连续按两次tab键
mkfs.ext4   /dev/sdb1    #格式化文件系统ext4
mkfs.xfs   /dev/sdb2     #格式化文件系统xfs
                                                          
blkid    /dev/sdb1    #查看文件系统类型  
blkid   /dev/sdb2     #查看文件系统类型

mkfs.xfs   -f    /dev/sdb2     #强制格式化文件系统xfs
```

###  2.4 挂载使用
#### 2.4.1 临时挂载
```
mkdir   /mypart1
mount   /dev/sdb1    /mypart1
df   -h    /mypart1  #显示正在挂载设备的使用情况显示

mkdir    /mypart2
mount    /dev/sdb2    /mypart2
df    -h     /mypart1    /mypart2 #显示正在挂载的设备信息，使用情况的显示
```
#### 2.4.2 开机自动挂载/etc/fstab
>**/etc/fstab**文件配置格式：
>>**设备路径    挂载点    文件系统类型   参数    备份标记(0不备份,1备份)   检测顺序(0不检测,1优先检测)**

```
[root@localhost ~]# blkid  /dev/sdb1   #查看文件系统类型
[root@localhost ~]# blkid  /dev/sdb2   #查看文件系统类型
[root@localhost ~]# vim    /etc/fstab    #vmware虚拟机
/dev/sdb1   /mypart1   ext4    defaults   0   0
/dev/sdb2   /mypart2    xfs    defaults   0    0
[root@localhost ~]# vim    /etc/fstab    #KVM虚拟机
/dev/vdb1   /mypart1   ext4    defaults   0   0
/dev/vdb2   /mypart2    xfs    defaults   0   0 
[root@localhost ~]# umount   /mypart1       #卸载
[root@localhost ~]# umount   /mypart2       #卸载
[root@localhost ~]# df  -h  |   grep  mypart  #没有输出
[root@localhost ~]# mount   -a         
检测/etc/fstab开机自动挂载配置文件,格式是否正确
检测/etc/fstab中,书写完成,但当前没有挂载的设备,进行挂载 
[root@localhost ~]# df  -h  |    grep  mypart  #有输出  
```

---

## 3. 分区步骤总结                            
1. 识别硬盘 lsblk
2. 分区规划 fdisk(MBR分区模式)、parted（GPT分区模式）
    * **<font color=red>parted /dev/sda print 可查看分区类型</font>**
3. 刷新分区表 partprobe
4. 格式化文件系统 mkfs.ext4、mkfs.xfs、blkid
5. 挂载   mount、/etc/fstab、mount -a、df -h

```
* lsblk                    列出系统的硬盘信息--硬盘
* blkid                    查看文件系统类型--文件系统
* parted /dev/sda print    可查看分区类型--分区类型
```

---

## 4. 交换空间（虚拟内存）
```
1. 关于交换空间的命令
mkswap    /dev/sdc1    #格式化交换文件系统
swapon                 #查看交换空间组成的成员信息    
swapon   /dev/sdc1     #启用交换分区
free  -h               #查看交换空间的大小
swapoff    /dev/sdc1   #停用交换分区

2. 开机自动启用交换分区  
[root@localhost ~]# vim    /etc/fstab   #增加一行信息
/dev/sdc1   swap    swap     defaults  0   0
```
---

## 5. 逻辑分区

```
80G硬盘进行（MBR分区模式）规划分区    
划分3个10G的主分区;2个20G的逻辑分区
[root@localhost ~]# fdisk  /dev/sdb   
n 创建主分区--->回车--->回车--->回车--->在last结束时 +10G
n 创建主分区--->回车--->回车--->回车--->在last结束时 +10G
n 创建主分区--->回车--->回车--->回车--->在last结束时 +10G
p 查看分区表
n 创建扩展分区 --->回车--->起始回车--->结束回车   将所有剩余空间给扩展分区
p 查看分区表
n 创建逻辑分区----->起始回车------>结束+20G
n 创建逻辑分区----->起始回车------>结束+20G
p 查看分区表
w 保存并退出
[root@localhost ~]# lsblk                   
[root@localhost ~]# parted  /dev/sdb print #查看分区类型
```

---

## 6. 逻辑卷

>逻辑卷的作用：**1.整合分散的空间   2.空间支持扩大**
>逻辑卷制作过程：**将众多的物理卷（PV）组建成卷组（V G），再从卷组中划分出逻辑卷（LV）**
>逻辑卷的条件：**1.不能是分区的剩余空间；2.必须是一个完整的分区或者完整的硬盘；3.未挂载的，未格式化的**

### 6.1 LVM管理工具集

|     功能     | 物理卷管理 |           |           |
| :----------: | :--------: | :-------: | :-------: |
|  Scan 扫描   |    pvs     |    vgs    |    lvs    |
| Create 创建  |  pvcreate  | vgcreate  | lvcreate  |
| Display 显示 | pvdisplay  | vgdisplay | lvdisplay |
| Remove 删除  |  pvremove  | vgremove  | lvremove  |
| Extend 扩展  |     /      | vgextend  | lvextend  |


### 6.2 制作卷组（VG）

```
 格式：vgcreate   卷组名    设备路径……
Successfully:成功   example：例子
[root@localhost ~]# man   vgcreate      #参考帮助信息
[root@localhost ~]# vgcreate  systemvg   /dev/sdb[1-2]
[root@localhost ~]# pvs    #查看系统所有物理卷信息
[root@localhost ~]# vgs    #查看系统卷组信息  
```

### 6.3 建立逻辑卷（LV）

```
 格式: lvcreate  -L   大小G    -n  逻辑卷名字     卷组名
[root@localhost ~]# lvcreate  -L  16G  -n  vo  systemvg
[root@localhost ~]# vgs    #查看卷组信息
[root@localhost ~]# lvs     #查看逻辑卷信息
```

### 6.4 使用逻辑卷（LV）

```
]# ls   /dev/systemvg/vo 
]# ls -l    /dev/systemvg/vo
                            
]# mkfs.xfs    /dev/systemvg/vo    #格式化xfs文件系统
]# blkid   /dev/systemvg/vo   #查看文件系统类型

]# vim  /etc/fstab
/dev/systemvg/vo   /mylv    xfs   defaults  0   0

]# mkdir    /mylv
]# mount   -a       #检测fstab文件内容书写是否正确
]# df    -h    /mylv    #查看查看正在挂载使用的设备
```

### 6.5 逻辑卷的扩展
1. **卷组有足够的剩余空间**

```
1.扩展逻辑卷的空间
]# df   -h   |   grep   vo
]# vgs
]# lvextend    -L   18G    /dev/systemvg/vo
]# vgs
]# lvs
2.扩展逻辑卷的文件系统（刷新文件系统）
xfs_growfs：刷新xfs文件系统
resize2fs：刷新ext4文件系统
]# xfs_growfs  /dev/systemvg/vo
]# df   -h   |   grep   vo
]# lvs
```

2. **卷组没有足够的剩余空间**

```
1.扩展卷组的空间
]# vgextend    systemvg     /dev/sdb{3,5,6}
]# vgs
2.扩展逻辑卷的空间    
]# vgs
]# lvextend    -L    25G     /dev/systemvg/vo
]# vgs
]# df   -h   |     grep   vo
3.扩展逻辑卷的文件系统（刷新文件系统）
]# xfs_growfs   /dev/systemvg/vo
]# df   -h    |    grep    vo
]# lvs
```

### 6.6 卷组划分空间的单位PE
* **默认1个PE的大小为4M**

```
1.
]# vgdisplay  systemvg     #显示卷组的详细信息
PE Size               4.00 MiB    #PE的大小

2. 请创建一个大小为250M的逻辑卷名字为lvredhat
]# vgchange  -s  1M  systemvg  #修改PE大小
]# vgdisplay  systemvg          #查看卷组详细信息
]# lvcreate  -L  250M  -n   lvredhat   systemvg
]# lvs

3. 创建卷组时，指定PE的大小
[root@nb ~]# vgcreate  -s  1M   systemvg  /dev/sdb[1-2]

•创建逻辑卷的时候指定PE个数
[root@nb ~]# vgcreate  -s  1M   systemvg  /dev/sdb[1-2]
    创建逻辑卷的时候指定PE个数
    –lvcreate  -l  PE个数  -n  逻辑卷名  卷组名  
[root@localhost ~]# lvcreate  -l  108  -n  lvhaha   systemvg
[root@localhost ~]# lvs
```

### 6.7 逻辑卷的删除
* **删除逻辑卷的前提：不能删除正在挂载使用的逻辑卷**

```
[root@localhost ~]# lvremove  /dev/systemvg/vo 
  Logical volume systemvg/vo contains a filesystem in use.
[root@localhost ~]# umount   /mylv/
[root@localhost ~]# lvremove  /dev/systemvg/vo
Do you really want to remove active logical volume systemvg/vo? [y/n]: y
  Logical volume "vo" successfully removed
[root@localhost ~]# lvs      #查看当前系统的所逻辑卷
[root@localhost ~]# vim /etc/fstab  #仅删除vo开机自动挂载

[root@localhost ~]# lvremove  /dev/systemvg/lvredhat 
Do you really want to remove active logical volume systemvg/lvredhat? [y/n]: y
  Logical volume "vo" successfully removed
删除卷组的前提：基于此卷组创建的所有逻辑卷，要全部删除
[root@svr1 ~]# lvs
[root@svr1 ~]# vgremove  systemvg    #删除卷组
[root@svr1 ~]# vgs        #查看当前系统的所有卷组信息
[root@svr1 ~]# pvremove   /dev/sdb{1,2,3,5,6}
[root@svr1 ~]# pvs      #查看当前系统的所有物理卷信息
```

---

## 7. RAID磁盘阵列
* **需要服务器硬件RAID卡**
    * 廉价冗余磁盘阵列
        * Redundant Arrays of Inexpensive Disks 
        * 通过硬件/软件技术，将多个较小/低速的磁盘整合成一个大磁盘
        * 阵列的价值：提升I/O效率、硬件级别的数据冗余
        * 不同RAID级别的功能、特性各不相同
        
```
•RAID 0，条带模式
–同一个文档分散存放在不同磁盘
–并行写入以提高效率
–至少需要两块磁盘组成，磁盘利用率100%

•RAID 1，镜像模式    
–一个文档复制成多份，分别写入不同磁盘
–多份拷贝提高可靠性，效率无提升
–至少需要两块磁盘组成，磁盘利用率50%

•RAID5，高性价比模式           
–相当于RAID0和RAID1的折中方案
–需要至少一块磁盘的容量来存放校验数据
–至少需要三块磁盘组成，磁盘利用率n-1/n
–提高可靠性，效率提升

•RAID6，高性价比/可靠模式
–相当于扩展的RAID5阵列，提供2份独立校验方案
–需要至少两块磁盘的容量来存放校验数据
–至少需要四块磁盘组成，磁盘利用率n-2/n

•RAID 0+1/RAID 1+0
–整合RAID 0、RAID 1的优势
–并行存取提高效率、镜像写入提高可靠性
–至少需要四块磁盘组成，磁盘利用率50%

```

---

## 8. VDO卷
* Virtual Data Optimizer（虚拟数据优化器）
    * 一个内核模块，目的是通过重删减少磁盘的空间占用，以及减少复制带宽
    * VDO是基于块设备层之上的，也就是在原设备基础上映射出mapper虚拟设备，然后直接使用即可
<br/>
* 重复数据删除
    * 输入的数据会判断是不是冗余数据
    * 判断为重复数据的部分不会被写入，然后对源数据进行更新，直接指向原始已经存储的数据块即可
<br/>
* 压缩
    * 对每个单独的数据块进行处理
    
```
[root@svr7 ~]# yum  -y  install   vdo     #所需软件包

•制作VDO卷
•vdo基本操作：参考man vdo 全文查找/example
–vdo  create  --name=VDO卷名称  --device=设备路径 --vdoLogicalSize=逻辑大小
–vdo  list
–vdo  status  -n  VDO卷名称
–vdo  remove  -n  VDO卷名称
–vdostats  [--human-readable] [/dev/mapper/VDO卷名称]

•VDO卷的格式化加速（跳过去重分析）：
–mkfs.xfs  –K   /dev/mapper/VDO卷名称
–mkfs.ext4  -E  nodiscard  /dev/mapper/VDO卷名称

前提制作VDO需要2G以上的内存
[root@nb ~]# vdo create --name=vdo0 --device=/dev/sdc --vdoLogicalSize=200G
[root@nb ~]# mkfs.xfs -K  /dev/mapper/vdo0 
[root@nb ~]# mkdir /nsd01
[root@nb ~]# mount   /dev/mapper/vdo0   /nsd01
[root@nb ~]# df -h
[root@nb ~]# vdostats --hum /dev/mapper/vdo0 #查看vdo设备详细信息

[root@svr7 ~]# vim /etc/fstab 
/dev/mapper/vdo0  /nsd01  xfs  defaults,_netdev  0  0 
```

---