#!/bin/bash

globalval1="hello"

function test() {
    globalval2="world"
    local localvar2="itcast"
    echo $localvar2
}

#local localvar1="itcast"

#调用函数
test

echo $globalval1 $globalval2 

#环境变量
export environVal="this is in environ"

#调用子脚本 <source ./xx.sh>不产生子进程，可以传变量 
./subScript.sh

#验证zi进程修改环境变量之后父进程有没有变化
echo $environVal

#删除变量
unset globalval1
echo "globalval1="$globalval1




