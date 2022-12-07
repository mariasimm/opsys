CC=gcc
test: obj/array.o obj/test_array.o include/array.h
	$(CC) -o test obj/*.o -L../../lib -lel -Wl,-rpath,../../lib

obj/array.o: src/array.c
	$(CC) -I./include -I../../include -c src/array.c -o obj/array.o

obj/test_array.o: src/test_array.c
	$(CC) -I./include -I../../include -c src/test_array.c -o obj/test_array.o 

init:
	mkdir src
	mkdir include
	mkdir obj
	mkdir lib

staticlib: obj/array.o
	ar r libar.a obj/array.o
	ranlib libar.a
	#ar rs librat.a obj/array.o
	mv libar.a lib/

sharedlib:
	$(CC) -I./include -I../../include -c -fpic src/array.c
	$(CC) -shared -o libar.so array.o
	mv libar.so lib/
	rm array.o

install:
	echo "Copy Lib and H files to directory"
	-cp include/array.h ../../include
	-cp lib/libar.a ../../lib
	-cp lib/libar.so ../../lib

