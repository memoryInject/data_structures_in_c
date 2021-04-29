CC = gcc
CFLAGS = -Wall
DEPS = binarySearchTree.h
OBJ = main.o binarySearchTree.o

%.o: %.c $(DEPS)
		$(CC) $(CFLAGS) -c -o $@ $<

main.out: $(OBJ)
		gcc $(CFLAGS) -o $@ $^
