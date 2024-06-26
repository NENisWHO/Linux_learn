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

