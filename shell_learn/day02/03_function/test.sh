#!/bin/bash

function testfunc
{
    echo "Testfunc"
    return 1
}

testfunc

echo $?


#返回字符串
testfunc2()
{
    echo "aaaaa"
    return 0
}

#使用命令代换的方式来获取函数的返回
var=`testfunc2`
echo $var


