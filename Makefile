CC=gcc
CFLAGS=-Wall -g -Wextra -pedantic -pthread -std=c99 -fsanitize=address,undefined

memgrind: memgrind.c mymalloc.c
	gcc -o memgrind memgrind.c mymalloc.c -I.

clean:
	rm -f memgrind