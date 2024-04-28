all: read write

read: 6_read.c
	gcc $< -o $@

write: 6_write.c
	gcc $< -o $@

.PHONY:clean
clean:
	rm -rf read write
