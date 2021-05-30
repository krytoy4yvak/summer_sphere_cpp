CC=g++
CFLAGS=-Wall -std=c++17
PROJECT=bigint
LIBNAME=lib$(PROJECT).a

all: $(LIBNAME)

$(LIBNAME): $(PROJECT).o
	ar rc $(LIBNAME) $(PROJECT).o

$(PROJECT).o: $(PROJECT).cpp $(PROJECT).h 
	$(CC) $(CFLAGS) -c $(PROJECT).cpp

clean:
	rm -rf *.o $(LIBNAME) test
	
test: $(LIBNAME) run_test
	./test $(LIBNAME)

run_test: test.o $(LIBNAME)
	$(CC) $(CFLAGS) -o test test.o -L. -l$(PROJECT)

test.o: test.cpp
	$(CC) -c test.cpp
