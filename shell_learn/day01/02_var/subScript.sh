#!/bin/bash

echo "this is a sub script"
echo $globalval1
echo "sub script end"

#从父进程拷贝环境变量到子进程
echo $environVal

#子修改父的环境变量
export environVal="22222"
