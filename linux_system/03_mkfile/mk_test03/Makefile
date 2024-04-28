OBJS = add.o sub.o mul.o div.o main.o
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


