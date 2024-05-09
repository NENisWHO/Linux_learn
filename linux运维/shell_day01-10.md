# shell_day01-10

[TOC]

## 0.前言
>训练素材来自B站阿铭linux：
>https://www.bilibili.com/video/BV1ih4y1Y7nh/?spm_id_from=333.788&vd_source=9f6a57780f9760d9cdd025dbc388f3ba
>感谢大佬的分享教程，视频内容对本人帮助很大。
## 1.day01

```shell
### 任务：
###     1.写一个脚本，遍历/data/目录下的txt文件
###     2.将txt文件备份
###     3.备份的文件名增加一个|年,月,日|的后缀，比如a.txt --> a.txt_20240101


#!/bin/bash

##定义后缀变量
suffix=`date +%Y%m%d`

##找到/data/目录下的txt文件，用for循环遍历
for f in `find . -type f -name "*.txt"`
do
    echo "备份文件$f"
    cp ${f} ${f}_${suffix}
    ##将生成的文件移到backups目录下
    mv ${f}_${suffix} ./backups
done
##关键知识点总结：
##1）date命令用法，可以根据日期、时间获取到想要的字符
##2）for循环如何遍历文件
```

## 2.day02

```shell
### 第二天练习题
### 需求：
###     创建3个用户，并给他们设置随机密码，密码记录在一个文件里，文件名userinfo.txt
###     用会从user_00 到 user_02
###     密码要求：保函大小写字母以及数字，密码长度15位

### ------- 分割线，以下为脚本正文 -------
#!/bin/bash 
##先查看/tmp/userinfo.txt文件是否存在，存在的话先删除，以免影响到脚本执行结果
if [ -f /tmp/userinfo.txt ]
then
    rm -rf /tmp/userinfo.txt
fi

##判断mkpasswd命令在不在，我们用该命令来生成随机字符串，也就是用户的密码
if ! which mkpasswd
then
    ##在这里，安装mkpasswd（红帽8）
    sudo yum install expect
fi

##借助seq生成从00到03, 3个数的队列
for i in `seq -w 0 02`
do
    ##每次生成一个随机字符串，将该字符串赋值给p变量，这个就是用户的密码
    ##mkpasswd默认生成的字符串会包含大小写字母和数字和特殊符号
    ##如果不要特殊符号，可以加-s 0来限制不使用特殊符号
    p=`mkpasswd -l 15 -s 0`
    ##添加用户，并给给用户设置密码
    useradd user_${i} && echo "${p}" | passwd --stdin user_${i}
    ##用户及用户密码追加到userinfo.txt文件中
    echo "user_${i} ${p}" >> /tmp/userinfo.txt
done

##关键知识点
## 1）mkpasswd可以生成随机字符串，-l指定长度，-s指定特殊字符的个数，-c指定小写字母个数
##    -C指定大写字母个数，-d指定数字个数
##
## 2）seq可以生成序列，用法：seq 1 5；seq 5；seq 1 2 10；seq 10 -2 1；seq -w 1 10
##
## 3）passwd --stdin username
```

## 3.day03

```shell
1.
### 第三天练习题
### 需求：
###	写一个检测脚本，用来检测本机所有磁盘分区读写是否都正常
###	提示：可以遍历所有挂载点，然后新建一个测试文件，
###	然后再删除测试文件，如果可以正常新建和删除，那说明该分区没问题

### ------- 分割线，以下为脚本正文 -------
#!/bin/bash

for mount_p in `df |sed '1d' |grep -v 'tmpfs' |awk '{print $NF}'`
do
    ## 创建测试文件，并删除，从而确定该磁盘分区是否有问题
    touch $mount_p/testfile && rm -rf $mount_p/testfile
    ## $?,含义：用于获取上一个shell命令的退出状态码，或者是函数的返回值
    if [ $? -ne 0 ]
    then
        echo "$mount_p 读写有问题"
    else 
        echo "$mount_p 读写正常"
    fi
done

### 关键知识点总结：
## 1）&& 连接符表示当前的命令执行成功才会执行后面的命令
##    在本例中，只有两条命令都执行成功了，才返回0 [shell中0为真，1为假]
##    否则任何一条命令执行出错，返回值都为非0
##
## 2）写脚本过程中，可以一边在命令行中运行命令调用一边写脚本
##
## 3）shell脚本里sed、grep、awk无处不在，三剑客
##    sed：sed命令来自英文词组stream editor的缩写，
##         其功能是利用语法/脚本对文本文件进行批量的编辑操作。
##         此处的 sed '1d': d为删除，1是一行--vim命令模式下的'1d'
##    grep：grep命令来自英文词组global search regular expression 
##          and print out the line的缩写，
##          意思是用于全面搜索的正则表达式，并将结果输出。
##          grep -v 显示不包含匹配文本的所有行
##    awk：其功能是对文本和数据进行处理。
##         awk '{print $NF}' 打印最后一列的数据
##         awk "{print $NF}" 会输出整行
##         NF来表示列数 $NF 表示打印出等于总列数的那一列的数据 
##

2.
#!/bin/bash
### $n
## $0
## 用于获取当前脚本文件名称
## $1~$9
## 代表输入的第一个参数到第9个参数 # 这都不用括号（要也不影响）
## 第10个以上就用数字比如{12} # 后面这些都必须要{ }括号
echo $0
echo "输出的第一个参数 $1"
echo "输出的第二个参数 $2"
echo "输出的第三个参数 $3"

### $#
##  语法：$#,含义：获取shell脚本所有输入参数的个数(输入2个就是2个)。
echo "输出的参数个数：${#}"
echo 输出的参数个数：$#
echo '输出的参数个数：${#}'
##### !!注意这里使用''单引号会原样输出

### $*、$@
##  语法：$*、$@,含义：都是获取所有传入参数，用于后续输出所有参数。
for item in "$*"
do
    echo $item
done

for item in "$@"
do
    echo $item
done

### $?
##  $?,含义：用于获取上一个shell命令的退出状态码，或者是函数的返回值
echo "hello"
echo $?

### $$
##  $$,含义：用于获取当前shell环境的进程ID号
echo $$

### 知识点总结：
### 4）Shell特殊变量讲解：$n、$#、$*、$@、$?、$$各自代表的意思及用法
##    参考链接：https://blog.csdn.net/nianjiuhuiyi/article/details/119640769
```

## 4.day04

```shell
## 检测/home/learn/Linux_learn/shell_learn/shell_train/4_check_up_data/data
## 目录下所有文件和目录，看是否满足下面条件：
## 1）所有文件权限为644
## 2）所有目录权限为755
## 3）文件和目录所有者为lenrn，所属组为root
## 如果不满足，改成符合要求
## 注意，不要直接改权限，一定要有判断的过程

### ------- 分割线，以下为脚本正文 -------
#!/bin/bash

cd /home/learn/Linux_learn/shell_learn/shell_train/4_check_up_data/data
##遍历所有目录和文件，用"find ."即可
for f in `find .`
do
    ##查看文件权限
    f_p=`stat -c %a $f`
    ##查看文件所有者
    f_u=`stat -c %U $f`
    ##查看文件所属组
    f_g=`stat -c %G $f`

    ##判断是否为目录
    if [ -d $f ]
    then 
        [ $f_p != '755' ] && chmod 755 $f
    else
        [ $f_p != '644' ] && chmod 644 $f
    fi

    ## &&在两条命令中间，可以起到if判断的作用
    ## 当第一条命令成功，才会执行后面的命令
    [ $f_u != 'learn' ] && chown learn $f
    [ $f_g != 'root' ] && chown :root $f
done

## ------- 分割线，以下为总结 -------
<<'COMMENT'
也可以用find实现
find /path -type d ! -prem 755 -exec chmod 755 {} \;
find /path ! -type d ! -prem 644 -exec chmod 644 {} \;
find /path ! -user learn -exec chown learn {} \;
find /path ! -group root -exec chgrp learn {} \;

两个脚本相比，第一个只需要find一次，而第二个需要find四次
如果文件量很大，执行效率很差。

### 关键知识点总结：
0）stat：参数-c，设置显示格式；
1）查看文件权限：  stat -c %a 1.txt
2）查看文件所有者：stat -c %U 1.txt
3）查看文件所属组：stat -c %G 1.txt
4）&& 可以实现：当前面命令成功 才执行 后面命令
5）|| 可以实现：当前面命令不成功 才执行 后面命令
COMMENT
```

## 5.day05

```shell
## shell脚本一天一练 -- Day5
## 今日脚本需求：
## 假如有一个目录/data/att/，该目录下有数百个子目录，
## 比如/data/att/aming， /data/att/linux
## 然后再深入一层为以日期命名的目录，例如 /data/att/aming/20231009,
## 每天会生成一个日期新目录，由于/data所在磁盘满了，
## 所以需要将老文件（一年以前的）挪到另外一个目录/data1/att下，
## 示例：mv /data/att/aming/20211001 /data1/att/aming/20211001
## 挪完之后，还需要作软链接，
## 示例：ln -s /data1/att/aming/20211001 /data/att/aming/20211001
## 写一个脚本，要求/data/att/下的所有子目录都要按此操作
## 脚本会每天01：00执行一次，任务计划无需考虑，只需要写脚本即可
## 提醒：要确保老文件成功挪动到/data1/att 下之后才能做软链接，需要有日志

### ------- 分割线，以下为脚本正文 -------

## 以这个目录为例/home/learn/linux_learn/shell_learn/shell_train/5_mv_data/data/att/


#!/bin/bash

## 先定义一个main函数，目的是为了后面调用函数，方便记录日志
main()
{
    cd ./data/att/
    ## 遍历第一层目录
    for dir in `ls`
    do
        ## 遍历第二层目录，用find只找到当前目录下一年以前的子目录
        for dir2 in `find $dir -maxdepth 1 -type d -mtime +365`
        do
            ## 将目标文件下的文件同步到/data1/att/目录下，注意之这里的-R可以自动创建目录结构
            rsync -aR $dir2/ /home/learn/linux_learn/shell_learn/shell_train/5_mv_data/data1/att
            if [ $? -eq 0 ]
            then
                ## 如果同步成功了，会将/data/att下的目录删除
                rm -rf $dir2
                echo "./data/att/$dir2 移除成功"
                ## 做软链接
                ln -s /home/learn/linux_learn/shell_learn/shell_train/5_mv_data/data1/att/$dir2 \
                    /home/learn/linux_learn/shell_learn/shell_train/5_mv_data/data/att/$dir2 && \
                echo "./data/att/$dir2 成功创建软链接"
                echo
            else
                echo "./data/att/$dir 未移除成功"
            fi
        done
    done
}

## 调用main函数，并将输出写入日志里，日志每天一个
main &> /tmp/move_old_data_`date +%F`.log

### ------- 分割线，知识总结 -------

<<'COMMENT'
关键知识点总结：
1）可以通过main函数的形式来方便定义脚本日志 "&>可以将错误信息或者普通信息都重定向输出"
2）find 使用-maxdepth定义查找目录层级
3）脚本某行很长的话，可以使用"\ + 回车" 来换行，但本质上还是一行内容
4）rsync的-R选项可以自动级联创建；目录层级
    rsync命令来自英文词组remote sync的缩写，其功能是远程数据同步。
    rsync命令能够基于网络（包含局域网和互联网）快速地实现多台主机间的文件同步工作。
5) ln -s 源文件名 目标文件名 "将源文件在目标文件目录下创建软链接"
6）可以通过touch -m -t [时间戳] 文件名 ;来修改文件的mtime（修改时间）
           touch -a -t [时间戳] 文件名 ;来修改文件的atime（访问时间）
                                                    ctime（修改权限的时)
    使用stat 文件名命令，例如：stat t.txt
    使用ls -lc 文件名命令，查看文件的ctime（change time）
    使用ls -lu 文件名命令，查看文件的atime（access time）
    使用ls -l 文件名命令，查看文件的mtime（modify time）
7）Linux 中&和&&, |和|| ,&> 与 >的区别
    & 表示任务在后台执行
    && 表示前一条命令执行成功时，才执行后一条命令
    | 表示管道，上一条命令的输出，作为下一条命令参数(输入)
    || 表示上一条命令执行失败后，才执行下一条命令，
    >符号是指：将正常信息重定向
    &>可以将错误信息或者普通信息都重定向输出

   ****************************
   * && 和 || 属于逻辑运算符号*
   * & 和 | 属于位操作符      *
   ****************************
COMMENT
```

## 6.day06

```shell
## shell脚本 --Day6
## 需求：
## 写一个监控脚本，监控系统负载，如果系统负载超过10,需要记录系统状态信息
## 提示：
##      1）系统负载命令使用uptime查看，过去1分钟的平均负载
##      2）系统状态使用以下工具标记：top、vmstat、ss
##      3）要求每隔20s监控一次
##      4）系统状态信息需要保存到/opt/logs/下面，保留一个月，文件名建议带有`date +%s`
##         后缀或者前缀

### ------- 分割线，以下为正文 -------

#!/bin/bash

## 首先看/opt/logs目录在不在，不在就创建
[ -d /opt/logs ] || mkdir -p /opt/logs

## while死循环--> while 
while :
do
    ## 获取系统1分钟的负载，并且只读取小数点前面的数字
    ## uptime 获取系统1分钟的平均负载
    ## awk -F 'average:' '{print $2}'；以average: "分割符"取第二部分
    ## cut -d',' -f1；以','为"分割符"取第一部分
    ## sed 's/ //g' 去掉每一行所有的空格
    load=`uptime |awk -F 'average:' '{print $2}' |cut -d',' -f1 |sed 's/ //g' |cut -d. -f1`
    if [ $load -gt 10 ]
    then
        ## 分别记录top、vmstat和ss命令的执行结果
        top -bn1 |head -n 100 &> /opt/logs/top.`date +%s`
        vmstat 1 10 &>  /opt/logs/vmstat.`date +%s`
        ss -an &> /opt/logs/ss.`date +%s`
    fi
    ## 休眠20秒
    sleep 20
    ## 找到30天以前的日志文件删除掉
    find /opt/logs \( -name "top*" -o -name "vmstat*" -o -name "ss*" \) \
        -mtime +30 |xargs rm -f
done

<<'COMMENT'
关键知识点总结：
1）死循环可以使用while : + sleep 组合

2）find里可以使用小括号将多个条件组合起来当成一条整体来处理

3) bash [参数] 文件名
       -n 检测脚本是否正确
       -x 显示执行过程详细信息   这里用 sh -x 最好
       -c 从字符串中读入命令
    
    使用sh命令
        -n 只读取shell脚本，检测语法错误，但不实际执行
        -x 进入跟踪方式，显示所执行的每一条命令
        -c "string" 从strings中读取命令
        -v 读取并打印出整个shell脚本，检测语法错误，但不实际执行

4） top命令的功能是实时显示系统运行状态，包含处理器、内存、服务、进程等重要资产信息。
    top 参数 对象
       -b 使用批处理模式，不进行交互式显示
       -n 设置显示的总次数，完成后自动退出

5） vmstat命令来自英文词组“Virtual Memory Statistics”的缩写，其功能是用于监视系统资源状态。
    vmstat [参数] [对象]

6） ss命令来自英文词组“Socket Statistics”的缩写，其功能是用于显示活动套接字信息。
    ss [参数]
        -a 显示所有参数
        -n 不解析域名

7）xargs命令来自英文词组extended arguments的缩写，用作给其他命令传递参数的过滤器。
COMMENT
```

## 7.day07

```shell
## -- Day7
## 需求：
##      有以台服务器作为web应用，用一个目录文件（/home/learn/shell_d/data/web/attachment)
##      不定时地会被用户上传新文件，但是不知道什么时候上传的
##      所以，需要我们每5分钟作一次检测是否有新文件生成。
##      写一个shell脚本检测。检测完成后若有新文件，
##      还需要将新文件的列表输出到一个按年、月、日、时、分为名字的日志里。
##      思路：每隔5分钟检测一次，那肯定需要一个计划任务，每5分钟去执行一次。
##      脚本检测的时候，就是使用find命令查找5分钟内有过更新的文件，
##      若有更新，那么这个命令会输出东西，否则是没有输出的。
##      所以，我们可以把输出结果的行数作为比较对象，看看它是否大于0

### ------- 分割线，正文 -------

#!/bin/bash 

## 日志文件名，包含年月日时分
d=`date +%Y%m%d%H%M`
basedir=/home/learn/shell_d/data/web/attachment

## find找到5分钟之内新产生的文件，并把文件列表写入一个文件里
find $basedir/ -type f -mmin -5 > /tmp/newf.txt

## 如果文件里有内容，把文件改名字，即我们要的文件列表日志文件
if [ -s /tmp/newf.txt ]; then
    /bin/mv /tmp/newf.txt /tmp/$d
fi

<<'COMMENT'
关键知识点总结：
1）find的 
        -mmin  选项以分钟为时间单位查找
        -mtime 选择以天为单位查找
2）[ -s filename ] 表示文件存在，并且文件内容不为空时，条件成立
COMMENT
```

## 8.day08

```shell
## Day8
## 需求：
##      输入一个数字，然后运行对应的命令。
## 显示命令如下：
##      "cmd meau" 1-date 2-ls 3-who 4-pwd
##      当输入1时，会运行date，输入2运行ls，以此类推

### ------- 分割线，以下为正文 -------

#!/bin/bash 
## 打印标识语
echo "*cmd meau** 1-date 2-ls 3-who 4-pwd"

## 使用死循环，目的是为了当用户输入的字符并非要求的数字时
## 不能直接退出脚本，而是再次重新开始
while :
do
    ## 然后使用read实现和用户界面交互，提示让用户输入一个数字
    read -p "please input a number 1-4: " n
    case $n in
        1)
            date
            ## 之所以要break，是因为当用户执行完命令就要推出脚本了
            break
            ;;
        2)
            ls
            break
            ;;
        3)
            who
            break
            ;;
        4)
            pwd
            break
            ;;
        *)
            ## 如果输入的并不是1-4的数字，提示出错
            echo "Wrong input, try again!"
            ;;
    esac
done

<<'COMMENT'
关键知识点总结：
1）read：
   read命令的功能是用于读取单行数据内容，一般是从标准输入中读取数值，用于给变量赋值。
   语法格式：read [参数] 变量名
                   -p 设置提示信息 --> 可以在shell脚本中实现和用户交互的效果
2）case ... esac 这种逻辑判断用法，非常适合做选择题，尤其是选项很多时
3）如果想反复和用户交互，必须使用while循环，并借助break或者continue来控制循环流程
4）break表示退出循环体，continue表示结束本次循环，进入下一次循环
COMMENT
```

## 9.day09

```shell
## Day9
## 需求：
##      写一个脚本执行后，打印一行提示"Please input a number:"
##      要求用户输入数值，然后打印出该数值，然后再>次要求用户输入数值。
##      直到用户输入"end"停止。

### ------- 分割线，以下为正文 -------

#!/bin/bash
## 死循环，做到用户反复输入
while :
do
    ## 提示语
    read -p "Please input a number:(input "end" to quit) " n
    ## 使用sed将用户输入的字符串中数字替换为空，如果是纯数字，那么num的值为1
    ## 为什么是1而不是0呢，因为wc -c会把回车也标记为1个字符
    num=`echo $n |sed -r 's/[0-9]//g' |wc -c`
    if [ $n == "end" ]
    then
        exit
    fi

    if [ $num -ne 1 ]
    then
        echo "What you input is not a number! Try again!"
    else
        echo "The number you entered is: $n"
    fi
done

<<'COMMENT'
关键知识点总结：
1） wc命令来自英文词组word count的缩写，
    其功能是统计文件的字节数、单词数、行数等信息，并将统计结果输出到终端界面。
    wc -c 计算字符串长度，其中回车也算是一个字符
       -l 统计行数
       -w 统计单词数
2）使用sed 's/[0-9]//g'可以将字符串里的数字删除
3）exit直接退出脚本
COMMENT
```

## 10.day10

```shell
## Day10
## 需求：
## 写一个监控脚本，检测某个站点访问是否正常
## 提示：
## 1）可以将访问的站点以参数的形式提供，例如：sh xx.sh www.aminglinux.com
## 2) 状态码为2xx或者3xx表示正常
## 3）正常时echo正常，不正常时echo不正常

### -------- 分割线，以下为正文 -------

#!/bin/bash

## 检测本机是否有curl命令
if ! which curl &>/dev/null 
then
    echo "本机没有安装curl"
    yum install curl -y
    if [ $? -ne 0 ]
    then
        echo "没有安装成功curl"
        exit 1
    fi
fi 
## 获取状态码
code=`curl --connect-timeout 3 -I $1 2>/dev/null|grep 'HTTP'|awk '{print $2}'`
## 如果状态马码是2xx或者3xx，则条件成立
if echo $code |grep -qE '^2[0-9][0-9]|^3[0-9][0-9]'
then
    echo "$1访问正常"
else
    echo “"$1访问不正常"
fi
<<'COMMENT'
1）curl：curl命令来自英文词组CommandLine URL的缩写，其功能是在Shell终端界面中基于URL规则进行文件传输工作。
    -I 显示网站的响应头信息
    --connect-timeout 设置最大请求时间
2）grep 
    -q 默认静态执行（不打印在终端，来判断真假）
COMMENT
```