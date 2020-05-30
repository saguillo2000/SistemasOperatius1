CFLAGS := -fPIC -O3 -g -Wall
CC := gcc
NAME := malloc_simple

lib: malloc.so

malloc.so: malloc_simple.o
	gcc -shared -o malloc.so malloc_simple.o

malloc_simple.o:malloc_simple.c
	gcc -c -fPIC malloc_simple.c

clean:
	$(RM) *.o *.so	