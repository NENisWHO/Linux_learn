#!/bin/bash

for FRUIT in apple banana pear
do
    echo "I like $FRUIT"
done


#1加到100
sum=0
for i in {1..100}; do
    sum=$[$sum+$i]
done

echo $sum

#遍历目录
for f in `ls`; do
    if [ -f "$f" ]
    then
        echo "$f is a regular file"
    elif [ -d "$f" ]
    then
        echo "$f is a directory"
    else
        echo "$f is not recognized"
    fi
done





