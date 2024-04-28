#!/bin/bash

sum=0
count=1
while [ $count -le 100 ]
do
    sum=$[$sum+$count]
    count=$[$count+1]
done

echo $sum


#密码输入

echo "please input passwd"
read try
errConut=1
while [ "$try" != "secret" ]
do
    if [ "$errConut" -ge 5 ]
    then
        echo "Error 5 time, exit"
        break
    fi

    echo "error, try again!"
    read try 
    errConut=$[$errConut+1]
done




