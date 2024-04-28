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
