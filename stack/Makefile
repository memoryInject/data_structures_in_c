CC = gcc
CFLAGS = -Wall
DEPS = stack.h
OBJ = main.o stack.o

%.o: %.c $(DEPS)
		$(CC) $(CFLAGS) -c -o $@ $<

main.out: $(OBJ)
		gcc $(CFLAGS) -o $@ $^
