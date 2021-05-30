CC = g++ --std=c++17

all: test

run_test: vector.h test.cpp
	$(CC) test.cpp -o test

test: run_test
	./test

clean:
	rm test