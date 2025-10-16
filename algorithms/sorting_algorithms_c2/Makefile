CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
SRC = sorting_algorithms.c
HEADER = sorting_algorithms.h

all: test_functionality test_performance

test_functionality: test_functionality.c $(SRC) $(HEADER)
	$(CC) $(CFLAGS) -o test_functionality test_functionality.c $(SRC)

test_performance: test_performance.c $(SRC) $(HEADER)
	$(CC) $(CFLAGS) -o test_performance test_performance.c $(SRC)

clean:
	rm -f test_functionality test_performance

.PHONY: all clean