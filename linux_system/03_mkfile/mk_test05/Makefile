#获取当前目录下的所有.c文件
SRC=$(wildcard ./*.c)

#将SRC中所有出现的.c替换成.o
OBJS=$(patsubst %.c,%.o, $(SRC))

TARGET = a.out
#$@ 表示目标
#$^ 所有依赖
#$< 第一个依赖


$(TARGET):$(OBJS)
	gcc $^ -o $@

%.o:%.c
	@gcc -c $< -o $@

#声明clean为伪目标，伪目标不去判断目标文件是否存在或者已经更新
#无条件执行
.PHONY:clean
clean:
	-rm -rf $(OBJS) $(TARGET)


