CC = gcc
CFLAGS = -Wall
DEPS = queue.h
OBJ = main.o queue.o

%.o: %.c $(DEPS)
		$(CC) $(CFLAGS) -c -o $@ $<

main.out: $(OBJ)
		gcc $(CFLAGS) -o $@ $^
