# 1_2 Linux Shell基础

[toc]

---

## 1. shell基本介绍

### 1.1 什么是shell

* 在Linux内核与用户之间的解释器程序；通常指 **/bin/bash（默认）**；负责向内核翻译及传达用户/程序指令；相当于操作系统的“外壳”。

### 1.2 shell使用方式
* 交互式（命令行）
    * 人工干预、智能化程度高、逐条解释执行、效率低
    
* 非交互式（脚本）
    * 需要提前设计、智能化难度大；批量执行、效率高；方便在后台悄悄运行
    
### 1.3 脚本的执行方式

1. 为脚本添加x权限，使用相对或者绝对路径执行
    * chmod <font color=red>u+x</font> test01.sh
    * ./test01.sh   或者   /opt/test01.sh --> **执行**
    * 用户（root）---bash---bash---echo 
2. 使用解释器程序执行脚本，无需x权限
    * bash test01.sh
    * 用户（root）---bash ---bash---echo   **会开启子进程**
3. 使用**source 或者.** 执行脚本，无需x权限
    * source test01.sh
    * 用户（root）---bash---echo		 **不会开启子进程**
    
### 1.4 脚本练习
```
1. 编写脚本，搭建yum
    #!/bin/bash
    #搭建yum软件仓库
    mkdir /abc
    mount /dev/cdrom /abc
    rm -rf /etc/yum.repos.d/*.repo
    echo "[abc]
    name=abcabc
    baseurl=file:///abc
    enabled=1
    gpgcheck=0" > /etc/yum.repos.d/abc.repo


2. 编写脚本，安装网站服务并开启，浏览网站时显示"web-test~~"
    #!/bin/bash
    #搭建网站
    yum -y install httpd
    echo "web-test~~" > /var/www/html/index.html
    systemctl restart httpd

3. 编写脚本，安装ftp服务并开启且设置为开机自启
    > 重定向标准输出
    2> 重定向错误输出
    &>  重定向所有输出

    #!/bin/bash
    yum -y install vsftpd &> /dev/null   //将不需要的信息扔黑洞
    systemctl restart vsftpd
    systemctl enable vsftpd
```

---

## 2. 变量的种类

### 2.1 自定义变量
* 可以的：
    * 名称可以用**数字、字母、下划线**，
* 不可以的：    
    * 不能以数字开头，
    * 不能使用特殊符号，
    * 等号两边不能有空格，
    
* 格式：**变量名称=值**

```shell
   a=10          //创建变量（对变量赋值），名字是a，值是10
   a=30          //再次赋值，之前的会被覆盖
   echo $a       //调用变量时使用$符号
   unset  a      //取消变量的定义
   a=            //将变量a赋值为空，效果同上
   echo ${a}RMB  //变量名容易与后续字符发生混淆时使用大括号隔开
```

### 2.2 环境变量，由系统提前定义好，使用时直接调用

```shell
    USER      # 当前用户名    
    UID       # 当前用户的id号    
    HOME      # 当前用户家目录
    HOSTNAME  # 主机名  
    SHELL     # 当前用户的解释器  
    PWD       # 当前位置
    PATH      # 存储命令的路径  
    PS1       # 一级提示符   
    PS2       # 二级提示符
```

### 2.3 位置变量与预定变量

```shell
    $1  # 执行脚本时后面第1个位置参数
    $2  # 执行脚本时后面第2个位置参数
    $3  # 执行脚本时后面第3个位置参数
    $*  # 执行脚本时后面所有位置参数
    $#  # 执行脚本时后面位置参数的个数
    $$  # 当前程序的进程号（该号码是随机的）
    $?  # 判断上一条指令是否执行成功，0是成功，非0是失败
```

### 2.4 变量应用实例

```shell
#!/bin/bash
useradd $1
echo "$2" | passwd --stdin $1
```
* env  查看所有环境变量
* set   查看所有变量

### 2.5 变量的扩展知识

#### 2.5.1 引号与反撇号
* 如有变量：**a=10**，
* **a=date仅仅是将四个字母赋值给a**；a=`date`是将date的执行结果赋值给a

|           |                      作用                       |    实例    |                   实例效果                    |
| :-------: | :---------------------------------------------: | :-------: | :------------------------------------------: |
|  双引号""  |                  **界定范围**                   | echo "$a" |                 正常调用变量                  |
|  单引号''  |         界定范围，**屏蔽特殊符号的功能**          | echo '$a' |             无法调用变量，\$被屏蔽             |
| 反撇号\`\` | **获取命令的执行结果，还可以使用$( )实现相同效果** | a=`date`  | 将date执行结果赋值给a(a=\$(date)   //效果同上) |

#### 2.5.2 read指令

* read 用来提示用户输出

```shell
    #!/bin/bash
    read -p "请输入用户名"  u   # -p是可以定义提示信息，u相当于自定义变量名称，可以存储用户看到提示信息后输入的字符
    useradd $u
    read -p "请输入密码"  n
    echo "$n" | passwd --stdin $u

# stty  -echo 屏蔽回显
# stty  echo  恢复回显

## 再次改良脚本：
    #!/bin/bash
    read  -p  "请输入用户名"  u
    useradd  $u
    stty  -echo
    read  -p  "请输入密码"  n
    stty  echo
    echo  "$n" | passwd  --stdin  $u
```

#### 2.5.3 定义变量初值（备用）
* 语法：${变量名:-初值}

```shell
#!/bin/bash
read -p "请输入用户名:"  u
[ -z $u ] && echo "必须输入用户名！"  && exit
useradd $u
read -p "请输入密码(默认123456):"  n
echo ${n:-123456} | passwd --stdin $u
```

---

## 3. 运算

1. expr命令

```shell
expr  1  +  1     //加法，运算符号两边要有空格
expr  2 – 1     //减法
expr  2  '*'  2  //乘法
expr  2  \*  2   // \是转义符号，可以屏蔽身后一个特殊符号的功能
expr  4  /  2   //除法
expr  5  %  2   //取余数
a=10
b=20
expr $a + $b
expr $a + 100
expr $a + $a
```

2. $[  ]与\$((  )) 可以实现相同效果

```
echo $[2*2]
echo $[2-2]
echo $[2/2]
echo $[2%2]
a=10
b=20
expr $a + $b
echo $[a+b]
```

3. let命令
    * **不输出结果，专用于变量的创建或者变量的自增减**

```
变量的自增减：
常规写法       主流写法
let a=a+1       let a++     变量a加1
let a=a-1	      let a--      变量a减1
let a=a+10      let a+=10   变量a加10
let a=a-10      let a-=10    变量a减10
let a=a*2       let a*=2     变量a乘以2
let a=a/2       let a/=2    变量a除以2
let a=a%3      let a%=3    变量a除以3取余数
```
4. bc,可以进行小数计算

---

## 4. $号的火花

```shell
## 1
a=10
echo $a # 调用变量时使用$符号
echo ${a}RMB  # 变量名容易与后续字符发生混淆时使用大括号隔开

## 2
$1  # 执行脚本时后面第1个位置参数
$2  # 执行脚本时后面第2个位置参数
$3  # 执行脚本时后面第3个位置参数
$*  # 执行脚本时后面所有位置参数
$#  # 执行脚本时后面位置参数的个数
$$  # 当前程序的进程号（该号码是随机的）
$?  # 判断上一条指令是否执行成功，0是成功，非0是失败

## 3
a=$(date) # 获取命令的执行结果，将结果赋值给变量a

## 4
# $[  ]、$((  )) 可以用来运算

```

---

## 5. 条件测试
* 作用：可以赋予脚本智能判断的能力
* 语法格式：
    * (1) test 表达式
    * (2) [ 表达式 ]
    
### 5.1 对字符串进行测试
* == 两边是否相等，**相等时条件测试算成功**
* != 两边是否不等，**不相等时条件测试算成功**

```
== 两边是否相等，相等时条件测试算成功
!= 两边是否不等，不相等时条件测试算成功
test a == a  //方式一：test ，使用常量判断，再用echo $?测试结果
test a == b  
[ a == a ]   //方式二：中括号，使用常量判断，再用echo $?测试结果
[ a == b ]   
a=abc
b=xyz
[ $a == $b ]  //使用变量判断两个变量的值是否相等
[ $a != $b ]   //使用变量判断两个变量的值是否不相等
[ "$c" == $b ]  //如果变量为空，有可能报错，加双引号可以避免

[ -z $a ]    //判断变量是否为空，为空时条件测试算成功
[ ! -z $a ]  //判断变量是否非空，非空时条件测试算成功
```

### 5.2 逻辑组合

1. 条件与指令
* **条件 &&  指令  ---   条件成功才执行指令**      
* **条件 ||   指令   ---  条件失败才执行指令**

```shell
[  root  ==  $USER  ] || exit   //判断当前用户名是否为root
如果判断失败，则执行exit
[  $USER  !=  root  ] && exit  //判断当前用户名是否不为root
如果判断成功，则执行exit
```

2. 多个逻辑符号组合

* A && B    A、B任务都成功算成功
* A || B     A、B 任务有一个成功算成功

```shell
touch a b c
ls a  &&  ls b  &&  ls c     //结果是都显示
ls a  ||  ls b  ||  ls c      //结果是显示a 
ls a  &&  ls b  ||  ls c     //结果是显示a和b
ls a  ||  ls b  &&  ls c     //结果是显示a和c

[ root != $USER ]  &&  echo "非管理员不能执行该脚本"  && exit  //之前
的语句可以改进成这个方式
```

### 5.3 数字
```
-eq  是否相等        equal
-ne  是否不等        not equal
-gt  是否大于        greater then
-ge  是否大于等于    greater or equal
-lt  是否小于        less then
-le  是否小于等于    less or equal 
```
* 编写脚本，每2分钟检查服务器的用户数量，如果发生变化则发邮件通知管理员

```
#!/bin/bash
x=$(cat /etc/passwd | wc -l)   //将目前用户数量赋值给变量x
[ $x -gt 29 ] && echo "用户数量发生变化，服务器可能被入  
侵" | mail -s test root       //如果目前用户数量大于29，就
发邮件给管理员，29是之前查看的用户数量

注意，以下命令不是脚本内容，要在命令行中敲，不写在脚本中
chmod  u+x  test01.sh   //然后给脚本加x权限
crontab  -e     //编写计划任务
*/2 * * * *  /opt/test01.sh    //定义每2分钟执行脚本
```

### 5.4 文件

```
-e  判断文件是否存在，不关心类型
-f  判断文件是否存在，必须是普通文件
-d  判断文件是否存在，必须是目录
-r  判断当前用户对文件是否有读权限，对root无效
-w  判断当前用户对文件是否有写权限，对root无效
-x  判断当前用户对文件是否有x权限
```

```shell
[ -e abc ]   //判断当前目录下的abc是否存在，用echo $?查结果
[ -f /opt/abc ]   //判断opt下有没有abc这个普通文件
[ -d /opt/abc ]  //判断opt下有没有abc这个目录mkdir  xyz
[ -d /opt/xyz ]   //判断opt下有没有xyz这个目录
[ -r /opt/abc ]   //判断当前用户对abc是否有读权限
[ -w /opt/abc ]   //判断当前用户对abc是否有写权限
[ -x /opt/abc ]   //判断当前用户对abc是否有x权限
```

---

## 6. if分支
> **分号";"的作用：不管前面成不成功，都会执行后面的命令**
1. 单分支
```
if 条件测试;then    //满足条件的话就执行下面指令
执行指令
fi
```

2. 双分支

```
if 条件测试;then    //满足条件的话就执行下面指令
执行指令A   //指令可以是一条，也可以是多条
else     //否则，不满足条件的话就执行下面指令
执行指令B
fi
```

3.  多分支

```
if 条件测试;then    //满足条件的话就执行下面A指令
执行指令A   //指令可以是一条，也可以是多条
elif 条件测试;then    //满足条件的话就执行下面B指令
执行指令B
elif 条件测试;then    //满足条件的话就执行下面C指令
执行指令C
else     //否则，不满足条件的话就执行下面指令
执行指令
fi
```

---

## 7. for循环

```
for 变量名称 in 值1  值2  值3 ...  //此处变量名可以自定义，通常习惯用i，值的多少决定了下面do与done之间的任务执行多少次，每个值之间有空格，这里是有3个值，所以就循环执行指令3次
do
任务
done

1. for i in a b c    //循环3次
 
2. for i in {1..100}    //循环100次，此处不支持变量，也就是不能写成{1..$a}的格式
 
3. for i in $(seq $a)    //这样可以支持变量定义循环次数，seq命令可以产生数字序列号
 
4. for i in $(cat  /opt/name.txt)    //循环批量创建name.txt里面所有用户，文档中每行是一个名字，该文档要提前创建，与脚本在同一目录下即可

5. for ((i=1;i<=5;i++))
```

---

## 8. while循环
* while：**可以根据条件决定循环次数，也可以实现无限循环**

```
while 条件测试   //根据条件的结果决定是否要执行任务，条件测试成功的话就执行，如果失败立刻结束循环
do
任务
done

1. while  :           //冒号代表永远正确，无限循环
2. while [ 1 -ep 1 ]  //无限循环
 
```

### 8.1 循环的控制

```
exit  可以终止循环，但脚本也终止
break  可以终止循环，继续循环后的任务
continue  可以终止当前循环，继续下一次循环
```

---

## 9. case 分支

```
1. 语法格式
case 调用的变量名 in
模式1)
指令;;
模式2)
指令;;
*)
指令
esac

2. 实例
#!/bin/bash
case $1 in
t)      //如果$1是t就执行touch任务
    touch $2;;
m)    //如果$1是m就执行mkdir任务
    mkdir $2;;
r)     //如果$1是r就执行rm任务
    rm -rf $2;;
*)
    echo "请输入t或者m或者r"
esac
```
---

## 10. 函数
* 作用：**利用一个名称存储公共的语句块，实现精简脚本方便后期调用的目的**
* 语法格式：
```
函数名(){
指令
}
```

* 实例：

```
1. 函数的声明与调用
a(){     //创建函数
echo abc
echo xyz
}
a   //调用函数
a   //可以反复调用函数

2.脚本中的实例
#!/bin/bash
a(){   //创建函数，名字叫a
echo -e "\033[$1m$2\033[0m"    //输出带颜色的字符
}
a 31 ABCD    //调用函数时，后面跟第一个位置变量定义颜色
第二个位置变量定义内容
a 32 xyzZ
a 33 EGSD
a 34 ERTY
a 35 BJYQ
```
---

## 11. 字符串
  
### 11.1 字符串的截取
* 语法：${变量名称:截取位置:截取长度}
* 编写脚本，可以生成8位随机字符用作密码

```shell
#!/bin/bash
x=abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789
for i in {1..8}
do
n=$[RANDOM%62]  //得到0~61随机数存在变量n中
a=${x:n:1}   //截取到1个随机字符，存在变量a中
c=$a$c   //不断往c中追加，此时c相当于一个袋子
done
echo $c   //最后喊出，得到8位长度随机字符串
```

### 11.2 字符串替换
* 语法格式：${变量名/旧/新}

```
a=1234
echo ${a/2/6}    //将1个字符2换成6
a=112233  
echo ${a/2/6}    //将1个字符2换成6
echo ${a//2/6}   //将所有字符2换成6
a=1122233
echo ${a/22/66}   //换2个
echo ${a/11/}    //将11替换成空，相当于删除
```

### 11.3 字符串的删除，可以删除两边
* 掐头：${变量名#要删除的内容} 
* 去尾：${变量名%要删除的内容}

```
a=abcdef   //创建变量，作为素材
echo ${a#abc}    //掐头,删除到abc
echo ${a%def}    //去尾,删除到def
echo ${a#abcde}    //掐头,删除到abcde

a=abcdefghijk   //创建变量，作为素材
echo ${a#abcdefghi}   //掐头,删除到i
echo ${a#*i}        //效果同上，精简写法
echo ${a%defghijk}  //去尾,删除到d
echo ${a%d*}      //效果同上，精简写法

a=abcdabcd   //定义变量为素材
echo ${a#*c}   //从左往右删除到第1个c
echo ${a##*c}  //从左往右删除到最后1个c
echo ${a%b*}  //从右往左删除到第1个b
echo ${a%%b*}  //从右往左删除到最后1个b
```

---

## 12. 正则表达式与linux三剑客

### 12.1 正则表达式
#### 12.1.1 基本正则表达式
| 正则符号 | 描述                                   |
| :------- | :------------------------------------ |
| ^        | 匹配行首                               |
| $        | 匹配行尾                               |
| []       | 集合，匹配集合中的任意单个字符           |
| [^]      | 对集合取反                             |
| .        | 匹配任意单个字符                        |
| *        | 匹配前一个字符任意次数(**不能单独使用**) |
| \{n,m\}  | 匹配前一个字符n到m次                    |
| \{n\}    | 匹配前一个字符n次                       |
| \{n,\}   | 匹配前一个字符n次以上                   |
| \{\}     | 保留                                   |
| \w       | 匹配数字、字母、下划线                  |
| \s       | 匹配空格、tab键                        |
| \d       | 匹配数字，和[0-9]等效                   |
```
* head -5 /etc/passwd > user    //准备素材

grep ^root user    //找以root开头的行
grep bash$ user     //找以bash结尾的行
grep ^$ user   //找空行
grep -v ^$ user  //显示除了空行的内容
grep "[root]" user    //找r、o、t任意一个字符 
grep "[rot]" user    //效果同上
grep "[^rot]" user   //显示r或o或t以外的内容
grep "[0123456789]" user   //找所有数字
grep "[0-9]" user    //效果同上
grep "[^0-9]" user   //显示数字以外内容
grep "[a-z]" user    //找所有小写字母
grep "[A-Z]" user    //找所有大写字母
grep "[a-Z]" user    //找所有字母
grep "[^0-9a-Z]" user   //找所有符号

grep "." user   //找任意单个字符，文档中每个字符都可
以理解为任意字符
grep "r..t" user  //找rt之间有2个任意字符的行
grep "r.t" user  //找rt之间有1个任意字符的行，没有匹
配内容，就无输出
grep "*" user   //错误用法，*号是匹配前一个字符任意
次，不能单独使用
grep "ro*t" user   //找rt，中间的o有没有都行，有几次都行
grep ".*" user  //找任意，包括空行 .与*的组合在正则中相当于通配符的效果

grep "ro\{1,2\}t" user  //找rt，中间的o可以有1~2个
grep "ro\{2,6\}t" user  //找rt，中间的o可以有2~6个
grep "ro\{1,\}t" user  //找rt，中间的o可以有1个以及1个以上
grep "ro\{3\}t" user   //找rt，中间的o必须只有有3个

```

#### 12.1.2 扩展正则表达式

| 正则符号 | 描述            |
| :------- | :-------------- |
| +        | 最少匹配一次     |
| ？       | 最多匹配一次     |
| {n,m}    | 匹配n到m次       |
| ()       | 组合为整体，保留 |
| \|       | 或者            |
| \b       | 单词边界         |

```
* 以上命令均可以加-E选项并且去掉所有\，改成扩展正则的用法，比如
grep "ro\{1,\}t" user可以改成 grep -E "ro{1,}t" user    
* 或者egrep "ro{1,}t" user   

grep "ro\{1,\}t" user   //使用基本正则找o出现1次以及1次以上
egrep "ro{1,}t" user   //使用扩展正则，效果同上，比较精简
egrep "ro+t" user   //使用扩展正则，效果同上，最精简
grep "roo\{0,1\}t" user   //使用基本正则找第二个o出现0~1次
egrep "roo{0,1}t" user   //使用扩展正则，效果同上，比较精简
egrep "roo?t" user   //使用扩展正则，效果同上，最精简

egrep "(0:){2}" user  //找连续的2个0:  小括号的作用是将字符组合为一个整体
egrep "root|bin" user  //找有root或者bin的行

egrep  "the\b" abc.txt   //在abc.txt文件中找the，右边不允许出
现数字、字母、下划线
egrep  "\bthe\b" abc.txt   //两边都不允许出现数字、字母、下划线
egrep  "\<the\>" abc.txt   //效果同上
```

### 12.2 sed流式编辑器

* 作用：可以对文档进行**非交互式增删改查**，**逐行处理**
* 用法：

```
1，前置指令 | sed  选项  条件  指令
2，sed  选项  条件  指令  被处理文档
* 选项:  
    * -n  屏蔽默认输出   
    * -r 支持扩展正则  
    * -i  修改源文件
* 指令：
    * p  输出   
    * d  删除   
    * s 替换
* 条件
    * 行号
    * /字符串/
    

一、输出
sed -n  'p'  user    //输出所有行
sed -n  '1p'  user   //输出第1行
sed -n  '2p'  user   //输出第2行
sed -n  '3p'  user    //输出第3行
sed -n  '2,4p'  user   //输出2~4行
sed -n  '2p;4p'  user   //输出第2行与第4行
sed -n '3,+1p' user   //输出第3行以及后面1行
sed -n '/^root/p' user   //输出以root开头的行  
sed -n '/root/p' user   //输出包含root的行
sed -nr '/^root|^bin/p' user   //输出以root开头的行或bin开头的行，|是扩展正则，需要r选项
sed -n '1!p' user   //输出除了第1行的内容，!是取反
sed -n '$p'  user  //输出最后一行
sed -n '='  user   //输出行号，如果是$=就是最后一行的行号

**以上操作，如果去掉-n,在将p指令改成d指令就是删除

二、删除
删除第3~5行   sed  '3,5d'  abc.txt
删除所有包含xml的行   sed  '/xml/d'   abc.txt
删除不包含xml的行   sed  '/xml/!d'   abc.txt
删除以install开头的行    sed  '/^install/d'   abc.txt
删除文件的最后一行  sed '$d' abc.txt
删除所有空行  sed  '/^$/d'  abc.txt

三、替换
sed 's/2017/6666/' shu.txt   //把所有行的第1个2017替换成6666
sed 's/2017/6666/2' shu.txt  //把所有行的第2个2017替换成6666
sed '1s/2017/6666/' shu.txt  //把第1行的第1个2017替换成6666
sed '3s/2017/6666/3' shu.txt  //把第3行的第3个2017替换成6666
sed 's/2017/6666/g' shu.txt   //所有行的所有个2017都替换
sed '/2024/s/2017/6666/g' shu.txt   //找含有2024的行，将里面的
所有2017替换成6666

如果想把 /bin/bash 替换成 /sbin/sh 怎么操作？
sed -i '1s/bin/sbin/' user   //传统方法可以一个一个换，先换一个
sed -i '1s/bash/sh/' user   //再换一个

如果想一起一步替换：
sed 's//bin/bash//sbin/sh/' user     //直接替换，报错
sed 's/\/bin\/bash/\/sbin\/sh/' user   //使用转义符号可以成功，但
不方便
sed 's!/bin/bash!/sbin/sh!' user   //最佳方案，更改s的替换符
sed 's(/bin/bash(/sbin/sh(' user   //替换符号可以用所有数字键上的

四、a行下追加   i行上添加   c替换整行
sed 'a 666' user    //所有行的下面追加666
sed '1a 666' user   //第1行的下面追加666
sed '/^bin/a 666' user   //在以bin开头的行的下面追加666
sed 'i 666' user  //所有行的上面添加666
sed '5i 666' user   //第5行的上面添加666
sed '$i 666' user  //最后1行的上面添加666
sed 'c 666' user   //所有行都替换成666
sed '1c 666' user  //替换第1行为666
```

### 12.3 awk

#### 12.3.1 awk基础
* 作用：可以实现精确搜索并输出 ，逐行处理
* 用法：

```
1. 前置指令 | awk 选项  条件  指令
2. awk 选项  条件  指令  被处理文档
* 选项：-F 定义分隔符
* 指令：print
* 条件：/字符串/
* 内置变量：
    * $1第一列  
    * $2第二列  
    * $3第三列 
    * $0 所有列   
    * NR行号   
    * NF 列号
    
awk '{print}' abc.txt    //输出所有
awk '/to/{print}' abc.txt    //输出有to的那行
awk '{print $2}' abc.txt    //输出所有行的第2列
awk '/to/{print $1}' abc.txt    //输出有to的那行的第1列
awk '{print $0}' abc.txt    //输出所有行所有列
awk '{print $0,$1}' abc.txt  //输出所有行所有列，第1列
awk '{print NR}' abc.txt   //输出所有行的行号
awk '{print NR,$0}' abc.txt   //输出所有行的行号，所有列
awk '{print NR,NF}' abc.txt   //输出所有行的行号，列号(有几列)

awk '/^bin/{print NR}'  user    //找以bin开头的行，显示该行的行号
awk '/^bin/{print NR,$0}'  user   //找以bin开头的行，显示该行的行号，所有列
awk '{print NF}'   user   //输出所有行的列号（每行有几列）
awk -F: '{print $1}'  user   //文档中如果没有空格，可以用F修改分隔符
awk -F: '{print $1,$6}'  user    //使用冒号作为列的分隔符，显示第1、6列
awk -F: '{print $1" 的家目录是 "$6}'  user    //还可以输出常量，加双引号即可
awk -F: '{print $1" 的解释器是 "$7}'  user
```

#### 12.3.2 awk的条件

```
1，/字符串/   还可以使用正则    ~ 包含   !~不包含
awk -F: '$6~/root/{print}'  user  //输出第6列包含root的行
awk -F: '$6~/bin/{print}'  user   //输出第6列包含bin的行
awk -F: '$6!~/bin/{print}'  user  //输出第6列不包含bin的行
2，使用数字或者字符串
==  !=  >  >=  <  <=
awk -F: '$3<3{print}' user   //输出第3列小于3的行
awk -F: '$3<=3{print}' user   //输出第3列小于等于3的行
awk -F: 'NR==2{print}' user   //输出第2行
awk -F: 'NR>2{print}' user    //输出行号大于2的行
3，逻辑组合  &&并且   ||或者
awk -F: 'NR==2||NR==4{print}' user   //找行号是2或者4的行
awk -F: 'NR==2||NR==40{print}' user   //如果只有一个条件满足就显示一个
awk -F: '$7~/bash/&&$3<=500{print}' user   //找第7列包含bash并且第3列小于等于500的行
awk 'NR==2&&NR==4{print}' user   //找行号既是2又是4的行，不存在，无输出
awk -F: '$7~/bash/&&NR<=3{print}' user  //找第7列包含bash并且行号是1~3的
awk -F: '$7~/bash/||NR<=3{print}' user  //找第7列包含bash或者行号是1~3的


awk -F: '$1~/root/' user    //找第1列包含root的行
如果有用户叫root6，也会搜到，比较宽松的搜索方式，如果
任务就是{print}的话可以省略不写
awk -F: '$1=="root"' user  //找第1列完全等于root的行
多一个字符少一个字符都不行，比较严格的搜索方式

4，运算
awk 'NR%2==0{print NR,$0}' user   //在条件中使用运算
，找到将行号除以2余数等于0的行，然后输出该行的行号和所有列，相当于输出偶数行
```

#### 12.3.3 awk处理时机，可以执行额外任务

```
BEGIN任务  执行1次，读取文档之前执行
逐行任务   执行n次，读取文档时执行 
END任务   执行1次，读取文档之后执行

awk 'BEGIN{print "User\tUID\tHome"}'   //第1步输出表头信息
awk -F: '{print $1"\t"$3"\t"$6}' user    //第2步输出内容
awk 'END{print "总计"NR"行" }' user    //第3步输出结尾
```

---


