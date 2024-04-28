
# shell_day1

1. **为什么要学习shell**
    - 简单的活就使用这种简单语言来开发
        - 日志文件，统计日志里边错误日志的条数
        - C/C++  半天
        - python / php /c# /java  2 小时
        - shell  几个命令搞定

    - 对linux的操作更加熟悉，更深的理解   

2. **passwd 文件**
        多行多列的表格  ，列的分隔符是冒号
        root : x : 0: 0:root:/root:/bin/bash

     - 用户名
    - （以前是将密码存放到第二列），如果是**x表示密码**通过加密放到了shadow
    - 用户id
    - 组id
    - 用户描述
    - home目录地址
    - 用户登录之后执行的第一条命令
        如果用户启动的第一条命令不是shell的话，就是执行完命令就退出了


3. **确定当前用户用什么shell**

    - echo $SHELL   查看环境变量
        看passwd文件用户的启动命令

    - 修改当前用户的shell ->  chsh

4. **shell 的内建命令**
    shell的内建命令是不会启动一个进程，而是就在当前shell的进程下去调用一个普通函数

5. **shell脚本的执行**
    1. **直接./执行**
        启动一个子进程 ；
        使用解释器解析脚本中的每一句命令；
        使用哪个解释器，在脚本的第一句指定
        #!/bin/bash；

            在子进程中cd 更换目录不会影响父进程

    2. **/bin/sh 脚本地址**
        也是启动一个子进程来执行，跟第一种方法作用类似,
        这种方法不需要脚本有可执行权限，**要有可读权限**
        在一些没办法调整脚本权限的情况下可以使用
        弊端：
            要调用者关注当前脚本使用什么解释器


    3. **(cd ..;ls -l)**
        也是启动一个子进程来执行；


    4. **source 脚本地址**
        这种方式执行脚本不会产生一个子进程，而是将脚本的命令都加载进来，执行常用于加载配置文件
        
              source /etc/profile
              .  跟 source 是同义词



6. **变量**
    - 声明即赋值
        varname=value
            注意等号**两边不能留空格**，留了空格就变成一个命令+两个参数


    - 使用变量
        $varname
        ${varname}

        a=1
        aa="hello"

        ${a}a
        ${aa}

        使用**花括号来限定变量名的范围**


7. **变量的分类**
    
- **shell 内变量**：在shell的解析环境中存在的变量
     - 全局范围的变量（全局变量）
            shell中不使用任何修饰符修饰的变量都是全局变量；
            不管是在函数内还是函数外都一样；
            从声明语句调用开始一直到脚本结束   都是其生命周期；
     - 局部变量
            用local 修饰；
            只能声明在函数内；
            从声明语句调用开始一直到函数结束；

    **shell内变量只能在当前shell进程中使用,跨了进程就不能用【source 不产生子进程可以传变量】；**

- **环境变量**：是操作系统自带的，每一个进程都会有
    - 当启动一个子进程的时候，环境变量是从父进程拷贝到子进程
    - 子进程做任何环境变量的修改，不会影响父进程
    - 环境变量是单向传递
        export varname=value
        或者  
        varname=value
        export varname
- **删除变量**
不管是环境变量还是普通的shell内变量，
都可以使用** unset 变量名进行删除**



8. **文件名代换**：**代换发生在命令执行之前**

    \* 匹配0个或多个任意字符
    ? 匹配一个任意字符
    [若干字符] 匹配方括号中任意一个字符的一次出现
    **代换成功的前提，文件必须存在，如果不存在是代换不了的**


9. **参数拓展**
    touch 1.txt 2.txt 3.txt 4.txt

    touch {1,2,3,4}.txt
    touch {1..4}.txt

    touch {1..4}_{5..6}.txt
    
    mkdir -p day{1..9}\0{1_doc,2_code,3_resource,4_note}
	
   
10. **命令代换**：执行某一条命令，将这个命令的标准输出的内容存到某个变量
    varname=\`cmd arg1 arg2 ...\`
    $(cmd) 跟 \`cmd\` 是一样

<mark>curPath=$(dirname \`$0\`;pwd)->获取当前脚本所在目录</mark>


11. **算数代换：做最基本的整数运算**

    - var=45
    $[var+1]
    $((var+3))

    - 进制转换
    echo $[8#10+11]
        将**10[幺零以8进制解释]**以8进制来解析，得到的是10进制的8，加上11 结果为19

12. **转义**
    - 将普通字符转成特殊字符：
        \r \n 
    - 将特殊字符转成普通字符：
        \$SHELL


13. **引号**
    - **单引号**
        保持字符串的字面值；
        即使字符串中有特殊符号也会转为普通符号；

    - **双引号**跟单引号一样，区别在于，支持变量的扩展
        <mark>作为一个有经验的shell程序员，使用变量之前，如果变量是作为一个参数来传递的，应该要习惯性的加双引号，防止变量中有空格</mark>

        var="a b"
        rm $var      删除两个文件 a b
        rm "$var"    删除一个文件 "a b"

14. **shell中如何表示真假**：**直接使用某条命令的返回状态来表示真假**
     
    main 函数的返回值
    **main函数返回 0 表示真**
    **main函数返回非0 表示假**

    <mark>跟C完全相反的</mark>

    通过 <mark>$? </mark> 来获取上一条命令的返回状态

15. **条件测试**
    
    - test 表达式
   
    
```
[ 表达式 ]：
中括号是一个单独的命令，后面的参数都是作为该命令的参数，所以要留空格
        
       ( EXPRESSION )
            测试该表达式是否为真

       ! EXPRESSION
            取反

       EXPRESSION1 -a EXPRESSION2
            逻辑与

       EXPRESSION1 -o EXPRESSION2
            逻辑或

       -n STRING
            判断字符串不是空串

            注意坑：

                test -n $var

       -z STRING
            判断字符串长度为0

       STRING1 = STRING2
            判断字符串相等

       STRING1 != STRING2
            判断字符串不等

       INTEGER1 -eq INTEGER2
            判断整数相等

       INTEGER1 -ge INTEGER2
            判断整数1>=整数2

       INTEGER1 -gt INTEGER2
            判断整数1>整数2

       INTEGER1 -le INTEGER2
            判断整数1<=整数2

       INTEGER1 -lt INTEGER2
            判断整数1<整数2

       INTEGER1 -ne INTEGER2
            判断整数1!=整数2

-------------------------------

       FILE1 -nt FILE2
            判断文件1比文件2新（指最后修改时间）

       FILE1 -ot FILE2
            判断文件1比文件2旧

       -b FILE
            块设备

       -c FILE
            字符设备

       -d FILE
            判断是否目录

       -e FILE
            单纯判断文件是否存在

       -f FILE
            判断文件是一个普通文件

       -h FILE
       -L FILE
            判断是否一个符号链接

       -k FILE
            判断文件的粘着位是否被设置

       -p FILE
            判断文件是否是一个命名管道


       -s FILE
            判断文件存在并且大小大于0字节

       -S FILE
            判断文件是否是一个socket文件

       -t FD
            判断某个文件描述符被终端打开
            
       -r FILE
            判断文件是否有读权限
            
       -w FILE
            判断是否有写权限

       -x FILE
            有执行权限
```

16. **分支结构if**
```
    if 命令|条件测试
    then
        xxxxxx
    elif 命令2|条件测试2 ; then    #如果then跟if写在同一行，加分号
        xxxxxx
    else      # else不用加then
        xxxxxx
    fi        # 将if倒着写
```

- 简单的分支结构判断和执行使用  && 和 ||

    - make && sudo make install**--->**如果make执行失败，**//短路特性**那么是不会走后面的命令 make install

    - echo xxxx ||  exit -1 ech**--->**如果前面的命令执行失败，那么就是执行后面的命令


17. **分支 case**
```
    c语言的switch
    switch(表达式)
    {
    case 值1:
        xxxx
        break;
    case 值2:
        xxxx
        break;
    default;
        xxxx
        break;
    }
```

```
    case 表达式 in
    val1|pattern1)
        xxxxxx
        ;;
    val2|pattern2)
        xxxxxx
        ;;
    *)
        xxxx
        ;;
    esac     #将case倒着写
```

18. **for**

```
    for varname in 列表 ; do  #do可以单独写一行，如果写在for这一样就要分号
        .....
        echo $varname
    done
----------------------------
    控制循环次数
    for i in {1..100}
    do
        ...
    done
----------------------------
    遍历目录
    for i in `ls`
    do
        ....
    done
```

19. **while**
```
    跟C一样
    while 命令|条件测试
    do
        xxxx
    done

    break 和 continue 跟C中的一样
```


20. **位置参数以及shift**

```
    $0          相当于C语言main函数的argv[0]
    $1、$2...    这些称为位置参数（Positional Parameter），相当于C语言main函数的argv[1]、argv[2]...
    $#          相当于C语言main函数的argc - 1，注意这里的#后面不表示注释
    $@          表示参数列表"$1" "$2" ...，例如可以用在for循环中的in后面。
    $*          表示参数列表"$1" "$2" ...，同上
    $?          上一条命令的Exit Status
    $$          当前进程号
    
    位置参数默认就支持10个 ，当然$@还是支持n个
    可以配合shift来进行参数左移，来操作不定参数
```

21. **输出**
```
    echo -n 表示不换行
    echo -e 解析转义字符
        echo -e "123\t234"

    printf "%d\t%s\n" 123 "hello"
        跟C的printf一样
```