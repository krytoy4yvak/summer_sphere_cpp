CC=g++
CFLAGS=-Wall -std=c++17 -O2
PROJECT=format
LIBNAME=lib$(PROJECT).a

all: $(LIBNAME)

$(LIBNAME): $(PROJECT).o  
	ar rc $(LIBNAME) $(PROJECT).o

$(PROJECT).o: $(PROJECT).cpp $(PROJECT).h
	$(CC) $(CFLAGS) -c $(PROJECT).cpp 

clean:
	rm -rf *.o $(LIBNAME) test
	
test: $(LIBNAME) run_test
	./test

run_test: test.o $(PROJECT).o 
	$(CC) $(CFLAGS) -o test test.o $(PROJECT).o

test.o: test.cpp $(PROJECT).h
	$(CC) -c test.cpp
