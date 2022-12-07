CC=gcc
test: obj/element.o obj/test_element.o include/element.h
	$(CC) -o test obj/*.o

obj/element.o: src/element.c
	$(CC) -I./include -c src/element.c -o obj/element.o

obj/test_element.o: src/test_element.c
	$(CC) -I./include -c src/test_element.c -o obj/test_element.o

init:
	-mkdir src
	-mkdir include
	-mkdir obj
	-mkdir lib
	touch src/element.c
	touch src/test_element.c
	touch include/element.h

staticlib: obj/element.o
	ar r libel.a obj/element.o
	ranlib libel.a
	#ar rs librat.a obj/element.o
	mv libel.a lib/

sharedlib:
	$(CC) -I./include -c -fpic src/element.c
	$(CC) -shared -o libel.so element.o
	mv libel.so lib/
	rm element.o

install:
	echo "Copy Lib and H files to directory"
	-cp include/element.h ../../include
	-cp lib/libel.a ../../lib
	-cp lib/libel.so ../../lib
