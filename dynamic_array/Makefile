CC = gcc
CFLAGS = -Wall
DEPS = dynamicArray.h
OBJ = main.o dynamicArray.o

%.o: %.c $(DEPS)
		$(CC) $(CFLAGS) -c -o $@ $<

main.out: $(OBJ)
		gcc $(CFLAGS) -o $@ $^
