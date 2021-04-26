CC = gcc
CFLAGS = -Wall 
DEPS = indexedBinaryHeap.h
OBJ = main.o indexedBinaryHeap.o

%.o: %.c $(DEPS)
		$(CC) $(CFLAGS) -c -o $@ $<

main.out: $(OBJ)
		gcc $(CFLAGS) -o $@ $^ -lm
