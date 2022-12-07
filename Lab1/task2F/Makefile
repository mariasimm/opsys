C=gcc
all:
	$(CC) -o test main.c -I./include -L./lib -lar -lel -Wl,-rpath,./lib
expand:
	$(CC) -E -o main.i main.c -I./include