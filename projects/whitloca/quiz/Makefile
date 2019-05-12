CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme: testme.o
	gcc -g testme.o -g $(CFLAGS)
	a.exe
	gcov -b testme.c

testme.o: testme.c
	gcc -c testme.c -g $(CFLAGS)