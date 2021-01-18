CC = gcc
CFLAGS = -Wall
DEPS = hashTableOpenAddressingBase.h hashTableLinearProbing.h hashTableQuadraticProbing.h hashTableDoubleHashing.h

linearProbing_OBJS = hashTableOpenAddressingBase.o hashTableLinearProbingTest.o
quadraticProbing_OBJS = hashTableOpenAddressingBase.o hashTableQuadraticProbingTest.o
doubleHashing_OBJS = hashTableOpenAddressingBase.o hashTableDoubleHashingTest.o

all: HashTableLinearProbing.out HashTableQuadraticProbing.out HashTableDoubleHashing.out run

HashTableLinearProbing.out: $(linearProbing_OBJS)
		$(CC) -o $@ $^

HashTableQuadraticProbing.out: $(quadraticProbing_OBJS)
		$(CC) -o $@ $^

HashTableDoubleHashing.out: $(doubleHashing_OBJS)
		$(CC) -o $@ $^

%.o: %.c $(DEPS)
		$(CC) $(CFLAGS) -c -o $@ $<


run: 
	./HashTableLinearProbing.out; ./HashTableQuadraticProbing.out; ./HashTableDoubleHashing.out	

.PHONY: all run
