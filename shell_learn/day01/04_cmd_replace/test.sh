#!/bin/bash
#dateTime=`date`
dateTime=$(date)

echo "dateTime is "$dateTime

#touch 1.txt

#获取当前脚本所在路径
curPath=$(cd `dirname $0`;pwd)
echo $curPath
touch $curPath/2.txt


#算术运算
var=2
var2=5
echo $((var+3))
echo $((var2+3))

echo $((8#10+11))

var3="a.txt b.txt"

touch $var3
touch "$var3"
