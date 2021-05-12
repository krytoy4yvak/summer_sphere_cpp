CC=g++
FLAGS=-Wall -std=c++17 -stdlib=libc++ -O2
NAME=liballocator.a

all: $(NAME)

$(NAME): allocator.o
	ar rc liballocator.a allocator.o

allocator.o: allocator.cpp allocator.h 
	$(CC) $(FLAGS) allocator.cpp -c

clean:
	rm -rf *.o $(NAME) test
	

run_test: $(NAME) test
	./test $(NAME)

test: test.o liballocator.a
	$(CC) -o test test.o -L. -lallocator

test.o: test.cpp
	$(CC) test.cpp -c
	
	
