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

    










