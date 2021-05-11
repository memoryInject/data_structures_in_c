CC = gcc
CFLAGS = -Wall
DEPS = suffixArray.h
OBJ = main.o suffixArray.o

%.o: %.c $(DEPS)
		$(CC) $(CFLAGS) -c -o $@ $<

main.out: $(OBJ)
		gcc $(CFLAGS) -o $@ $^
