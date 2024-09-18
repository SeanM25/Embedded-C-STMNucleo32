all: Lab06

Lab06: sort.c LinkedList.o BOARD.o
	gcc -Wall sort.c LinkedList.o BOARD.o -o Lab06

LinkedListTest: LinkedListTest.c LinkedList.o BOARD.o
	gcc -Wall LinkedListTest.c LinkedList.o BOARD.o -o LinkedListTest

LinkedList.o: LinkedList.c
	gcc -Wall -c LinkedList.c

BOARD.o: BOARD.c
	gcc -Wall -c BOARD.c
