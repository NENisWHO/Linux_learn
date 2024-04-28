#!/bin/bash

visit()
{
    #全局变量会有逻辑错误，要使用局部变量
    local dir="$1"
    for f in `ls $1`
    do
        if [ -f "$dir/$f" ]
        then
            echo "$dir/$f is a file"
        elif [ -d "$dir/$f" ]
        then 
            echo "$dir/$f is a dir"
            visit "$dir/$f"
        else
            echo "$dir/$f is not recognized"
        fi
    done

}


visit .
