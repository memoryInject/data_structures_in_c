CC = gcc
CFLAGS = -Wall
DEPS = hashTable.h
OBJ = main.o hashTable.o

%.o: %.c $(DEPS)
		$(CC) $(CFLAGS) -c -o $@ $<

main.out: $(OBJ)
		gcc $(CFLAGS) -o $@ $^
