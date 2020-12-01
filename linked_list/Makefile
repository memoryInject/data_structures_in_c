CC = gcc
CFLAGS = -Wall
DEPS = linkedList.h
OBJ = main.o linkedList.o

%.o: %.c $(DEPS)
		$(CC) $(CFLAGS) -c -o $@ $<

main.out: $(OBJ)
		gcc $(CFLAGS) -o $@ $^
