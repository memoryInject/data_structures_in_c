CC = gcc
CFLAGS = -Wall
DEPS = unionFind.h
OBJ = main.o unionFind.o

%.o: %.c $(DEPS)
		$(CC) $(CFLAGS) -c -o $@ $<

main.out: $(OBJ)
		gcc $(CFLAGS) -o $@ $^
