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
