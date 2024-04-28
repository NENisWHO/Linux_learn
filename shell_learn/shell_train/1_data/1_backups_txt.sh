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


