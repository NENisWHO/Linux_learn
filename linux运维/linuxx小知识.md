# linuxx小知识

## 1. 给普通用户添加sudo权限
```
1. 先给/etc/sudoers 设置权限为640
2. 然后 vim /etc/sudoers
   找到           root ALL=(ALL:ALL) ALL
   在下一行添加    user ALL=(ALL:ALL) ALL
3. 再将/etc/sudoers 权限设置回440
```
## 2. 内存使用情况
```
1. free
     -m 选项是以MB为单位来展示内存使用信息; 
     -h 选项则是以人类(human)可读的单位来展示。
     
    total 表示总共有 **MB 的物理内存(RAM);
    used 表示物理内存的使用量;
    free 表示空闲内存;
    shared 表示共享内存;
    buff/cache 表示缓存和缓冲内存量;Linux 系统会将很多东西缓存起来以提高性能，这部分内存可以在必要时进行释放，给其他程序使用。
    available 表示可用内存;
    Swap 这一行表示交换内存;

2. 查看 /proc/meminfo
    MemTotal, 总内存
    MemFree, 空闲内存
    MemAvailable, 可用内存
    Buffers, 缓冲
    Cached, 缓存
    SwapTotal, 交换内存
    SwapFree, 空闲交换内存
3. 使用 vmstat 命令
    使用 vmstat -s 命令和选项, 可以对内存使用情况进行统计， 类似于 /proc/meminfo。

4. 使用 top 命令
    top 命令一般用于查看进程的CPU和内存使用情况；当然也会报告内存总量，以及内存使用情况，所以可用来监控物理内存的使用情况。
```

## 3. Rocky8 Linux 换成阿里云仓库
```
# 换源
sed -e 's|^mirrorlist=|#mirrorlist=|g' \
    -e 's|^#baseurl=http://dl.rockylinux.org/$contentdir|baseurl=https://mirrors.aliyun.com/rockylinux|g' \
    -i.bak \
    /etc/yum.repos.d/Rocky-*.repo

# 生成缓存
dnf makecache

# 查看镜像仓库
yum repolist
```
## 4. 配置终端命令行颜色
```
1. 在终端中输入 set | grep "PS1"
   可以查看PS1的设置
2. PS1='[\u@\h \W]\# '  
   这是我的rocky8虚拟机root用户默认
   的PS1设置；
   
   \u 表示用户（username)；
   \h 表示主机(hostname)；
   \w 表示当前工作目录(directory)；
   $ 如果您不是超级用户 (非root)，则插入一个 “$”；
   如果您是超级用户（root），则显示一个 “#”。

3. PS1中参数含义
\d ：代表日期，格式为weekday month date，例如："Mon Aug 1"   
 
\e： ASCII转义字符
 
\H ：完整的主机名称   
 
\h ：仅取主机的第一个名字  
 
\j：shell当前管理的作业数
 
\1：shell终端设备名的基本名称
 
\n：ASCII换行字符
 
\r：ASCII回车
 
\s：shell的名称
 
\t ：显示时间为24小时格式，如：HH：MM：SS   
 
\T ：显示时间为12小时格式   
 
\@：格式为am/pm的12小时制的当前时间
 
\A ：显示时间为24小时格式：HH：MM   
 
\u ：当前用户的账号名称   
 
\v ：BASH的版本信息   
 
\V：bash shell的发布级别
 
\w ：完整的工作目录名称   
 
\W ：利用basename取得工作目录名称，所以只会列出最后一个目录   
 
\ ：下达的第几个命令   
 
\!：该命令的bash shell历史数
 
\#：该命令的命令数量
 
\$ ：提示字符，如果是普通用户，则为美元符号$；如果超级用户（root 用户），则为井号#。
 
\nnn：对应于八进制值 nnn 的字符
 
\\：斜杠
 
\[：控制码序列的开头
 
\]：控制码序列的结尾


字体颜色：
	30m==黑色;　　　　31m==红色;　　　　   
	32m==绿色;　　　　33m==黄色;
	34m==蓝色;　　　　35m==洋红;　　　
	36m==青色;　　　　37m==白色；
背景颜色：
	40m==黑色;　　　　41m==红色;　　　
	42m==绿色;　　　　43m==黄色;
 	44m==蓝色;　　　  45m==洋红;　　　 
    46m==青色;　　　　47m==白色
颜色截至：
    \[\e[0m\]
其他功能数字：
    0==OFF
  	1==高亮显示（我使用的就是高亮）
  	4==underline
  	5==闪烁
  	7==反白显示
  	8==不可见
4. 配置 .bashrc
PS1='\[\e[1;35m\]\u@\h:\[\e[0m\]\[\e[1;33m\]\W\[\e[1;35m\]\[\e[0m\]\[\e[1;34m\]\$ \[\e[0m\]'

5. .bashrc生效
    source .bashrc 就可以了
    
参考链接：[CSDN](https://blog.csdn.net/apollo_miracle/article/details/116007968)
```

## 5. 配置vim
```
#!/bin/bash
echo "This script will install and configure vim and zsh automatic."
echo "The time this takes is related to the network conditions, please wait patiently."
if [[ `whoami` == "root" ]];then
    echo -e "\033[31mYou are  running this script with Root\033[0m"
    echo -e "\033[31mGenerally, we do not recommend using root for programming or directly controlling your Linux OS, especially when you are a beginner \033[0m"
    echo -e "\033[31mSo, There is no necessary for you to configure with root."
    read -p "Do you really want to do this?[N/y]" choice
    if [[ ${choice} != y ]];then
    	echo "Bye."
    	exit 1
    fi
fi
if which apt-get >/dev/null; then
	sudo apt-get install -y vim  universal-ctags  xclip astyle python-setuptools  git wget
elif which yum >/dev/null; then
	sudo yum install -y gcc vim git ctags xclip astyle python-setuptools python-devel wget	
fi

##Add HomeBrew support on  Mac OS
if which brew >/dev/null;then
    echo "You are using HomeBrew tool"
    brew install vim ctags git astyle
fi

sudo easy_install -ZU autopep8 
sudo ln -s /usr/bin/ctags /usr/local/bin/ctags
rm -rf ~/vim* 2>&1 >/dev/null
rm -rf ~/.vim* 2>&1 >/dev/null
mv -f ~/vim ~/vim_old
cd ~/ && git clone https://gitee.com/suyelu/vim.git
mv -f ~/.vim ~/.vim_old 2>&1 >/dev/null
mv -f ~/vim ~/.vim 2>&1 >/dev/null
mv -f ~/.vimrc ~/.vimrc_old 2>&1 >/dev/null
mv -f ~/.vim/.vimrc ~/ 
git clone https://gitee.com/suyelu/vundle.git ~/.vim/bundle/vundle
echo "程序正在自动安装相应插件" > kaikeba
echo "command-t插件需要等待时间较长，不要担心" >> kaikeba
echo "切勿强制退出该界面，否则会导致错误，需重新配置" >> kaikeba
echo "安装完毕将自动退出" >> kaikeba
echo "请耐心等待" >> kaikeba
vim kaikeba -c "BundleInstall" -c "q" -c "q"
rm kaikeba
echo "安装完成"

参考链接：[宿船长的Notion](https://suyelu.notion.site/Vim-df538ebfd7744ef8ae5b6c27e3611522)
```


## 6. 查看文件的时间
```
1. stat filename
    - Access 文件最近访问时间 <--> ATime
    - Modify 文件内容最近修改时间 <--> MTime
    - Change 文件属性最近修改时间 <--> CTime

2. touch 参数 文件名
    -a 修改ATime
    -d 使用指定日期来修改
    -r 把指定的文件日期更设成和参考文档或目录日期相同的时间
    

参考：[CSDN](https://blog.csdn.net/qq_31828515/article/details/62886112)
```
