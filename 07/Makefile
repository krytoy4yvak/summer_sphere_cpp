CC=g++
CFLAGS=-Wall -std=c++14
PROJECT=vector
LIBNAME=lib$(PROJECT).a

all: $(LIBNAME)

$(LIBNAME): $(PROJECT).h  
	ar rc $(LIBNAME) $(PROJECT).h 

clean:
	rm -rf *.o $(LIBNAME) test
	
test: $(LIBNAME) run_test
	./test $(LIBNAME)

run_test: test.o $(LIBNAME)
	$(CC) $(CFLAGS) -o test test.o -L -l$(PROJECT)

test.o: test.cpp
	$(CC) -c test.cpp
	
vgcheck: $(LIBNAME) run_test
	valgrind --tool=memcheck --leak-check=full -s ./test $(LIBNAME)
