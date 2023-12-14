CC=gcc
CFLAGS = -g -Wall -pedantic 
MAINDEP = main.o library.o index.o
EXPECT_SCRIPT = add_data_test.sh

all: main 

test:
	expect $(EXPECT_SCRIPT)

main: $(MAINDEP)
	$(CC) $(CFLAGS) -o $@ $(MAINDEP)

%.o : %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

run: 
	./main first_fit test

runv:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./main first_fit test || true



clean: 
	rm -f *.o main

.PHONY: all test clean
