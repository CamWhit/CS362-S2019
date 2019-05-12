CFLAGS= -Wall -fpic -coverage -lm -std=c99

default: testme

testme: testme.o
	gcc -g testme.o -g $(CFLAGS)
	gcov -b testme.c
	a.exe

testme.o: testme.c
	gcc -c testme.c -g $(CFLAGS)