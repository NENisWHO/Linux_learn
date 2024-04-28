OBJS = add.o sub.o mul.o div.o main.o
TARGET = a.out
#$@ 表示目标
#$^ 所有依赖
#$< 第一个依赖


$(TARGET):$(OBJS)
	gcc $^ -o $@

add.o:add.c
	gcc -c $< -o $@

sub.o:sub.c
	gcc -c $< -o $@


mul.o:mul.c
	gcc -c $< -o $@

div.o:div.c
	gcc -c $< -o $@

main.o:main.c
	gcc -c $< -o $@

clean:
	rm -rf $(OBJS) $(TARGET)


