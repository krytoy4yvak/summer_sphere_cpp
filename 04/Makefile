CC=g++
CFLAGS=-Wall -std=c++17 -O2
PROJECT=serializer
LIBNAME=lib$(PROJECT).a

all: $(LIBNAME)

$(LIBNAME): serializer.h deserializer.h 
	ar rc $(LIBNAME) serializer.h deserializer.h

clean:
	rm -rf *.o $(LIBNAME) test
	
test: $(LIBNAME) run_test
	./test $(LIBNAME)

run_test: test.o $(LIBNAME)
	$(CC) -o test test.o -L -l$(PROJECT)

test.o: test.cpp
	$(CC) $(CFLAGS) -c test.cpp
	
vgcheck: $(LIBNAME) test
	valgrind --tool=memcheck --leak-check=full -s ./test $(LIBNAME)
