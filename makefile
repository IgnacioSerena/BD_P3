CC=gcc
CFLAGS = -g -Wall -pedantic 
MAINDEP = main.o library.o index.o
EXPECT_SCRIPT = cli_tests.sh

all: main 

test:
	expect add_data_test.sh

main: $(MAINDEP)
	$(CC) $(CFLAGS) -o $@ $(MAINDEP)

%.o : %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

run: 
	./main first_fit test

runv:
	valgrind --track-origins=yes ./main first_fit test

clean: 
	rm -f *.o main test

.PHONY: all test clean