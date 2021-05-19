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
	rm -rf *.o $(NAME) test TEST_FILE.txt
	
test: $(NAME) run_test
	./test $(NAME)

run_test: test.o $(NAME)
	$(CC) -o test test.o -L. -l$(PROJECT)

test.o: test.cpp
	$(CC) -c test.cpp
	
vgcheck: $(NAME) test
	valgrind --tool=memcheck --leak-check=full -s ./test $(NAME)
