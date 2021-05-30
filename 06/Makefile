
CC = g++ --std=c++17

all: test

run_test: test.cpp format.h
	$(CC) test.cpp -o test

test: run_test
	./test

clean:
	rm -f test