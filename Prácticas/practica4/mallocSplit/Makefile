CFLAGS := -fPIC -O3 -g -Wall
CC := gcc
NAME := malloc_split_and_merge

lib: malloc.so

malloc.so: malloc_split_and_merge.o
	gcc -shared -o malloc.so malloc_split_and_merge.o

malloc_split_and_merge.o: malloc_split_and_merge.c
	gcc -c -fPIC malloc_split_and_merge.c

clean:
	$(RM) *.o *.so	
