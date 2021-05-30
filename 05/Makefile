CC=g++
CFLAGS=-Wall -std=c++17 -O2

all: test

test: run_test
	./test

run_test: test.cpp serializer.h
	$(CC) $(CFLAGS) test.cpp -o test

clean:
	rm test