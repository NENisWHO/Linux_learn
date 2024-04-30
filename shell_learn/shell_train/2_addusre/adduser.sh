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

