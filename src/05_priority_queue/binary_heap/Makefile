CC = gcc
CFLAGS = -Wall
DEPS = binaryHeap.h
OBJ = main.o binaryHeap.o

%.o: %.c $(DEPS)
		$(CC) $(CFLAGS) -c -o $@ $<

main.out: $(OBJ)
		gcc $(CFLAGS) -o $@ $^
