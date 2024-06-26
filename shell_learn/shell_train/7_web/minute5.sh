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



