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
	gcc -c $< -o $@

clean:
	rm -rf $(OBJS) $(TARGET)


