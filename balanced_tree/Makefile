CC = gcc
CFLAGS = -Wall
DEPS = AVLTree.h
OBJ = main.o AVLTree.o

%.o: %.c $(DEPS)
		$(CC) $(CFLAGS) -c -o $@ $<

main.out: $(OBJ)
		gcc $(CFLAGS) -o $@ $^
