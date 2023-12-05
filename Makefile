CC=gcc
CFLAGS = -g -Wall -pedantic 
LIBRARYDEP = library.o types.h
EXPECT_SCRIPT = cli_tests.sh

all: library test

test:
	chmod +x $(EXPECT_SCRIPT) 
	./$(EXPECT_SCRIPT)

library: $(LIBRARYDEP)
	$(CC) $(CFLAGS) -o $@ $(LIBRARYDEP)

%.o : %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean: 
	rm -f *.o library test

.PHONY: all test clean