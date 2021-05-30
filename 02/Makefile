CC=g++
CFLAGS= --std=c++17
NAME=libparser.a

all: $(NAME)

$(NAME): parser.o
	ar rc libparser.a parser.o

parser.o: parser.cpp parser.h 
	$(CC) $(CFLAGS) -c parser.cpp

clean:
	rm -rf *.o $(NAME) test
	
test: $(NAME) run_test
	./test $(NAME)

run_test: test.o libparser.a
	$(CC) $(CFLAG) -o test test.o -L. -lparser

test.o: test.cpp
	$(CC) $(CFLAGS) -c test.cpp
	