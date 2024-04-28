#!/bin/bash   

echo "It is morning? Please answer yes or no!"

#读取用户输入一个变量
read YES_OR_NO

if [ "$YES_OR_NO" = "yes" ]
then
    echo "Good morning"
elif [ "$YES_OR_NO" = "no" ]
then
    echo "Good afternoon"
else
    echo "NOt recognized"
fi


var1=1; var2=2
if [ $var1 -eq 1 ] && [ $var2 -eq 2 ]
then
    echo "yes"
fi





