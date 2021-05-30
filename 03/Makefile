CC=g++
CFLAGS=-Wall -std=c++17 -O2
PROJECT=matrix
NAME=lib$(PROJECT).a

all: $(NAME)

$(NAME): $(PROJECT).o
	ar rc $(NAME) $(PROJECT).o

$(PROJECT).o: $(PROJECT).cpp $(PROJECT).h 
	$(CC) $(CFLAGS) -c $(PROJECT).cpp

clean:
	rm -rf *.o $(NAME) test
	
test: $(NAME) run_test
	./test $(NAME)

run_test: test.o $(NAME)
	$(CC) $(CFLAGS) -o test test.o -L. -l$(PROJECT)

test.o: test.cpp
	$(CC) -c test.cpp
