CC = gcc
CFLAGS = -Wall
DEPS = fenwickTree.h
OBJ = main.o fenwickTree.o

%.o: %.c $(DEPS)
		$(CC) $(CFLAGS) -c -o $@ $<

main.out: $(OBJ)
		gcc $(CFLAGS) -o $@ $^

run:
	./main.out

.PHONY: main.out run 
