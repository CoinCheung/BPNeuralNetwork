CppC = g++
CC = gcc
CFLAGs = -c -g -std=c99
CppFLAGs = -c -g -std=c++11 $(shell pkg-config --cflags openblas) -fno-elide-constructors -Wall
LFLAGs = -ltcmalloc -lpthread -lm $(shell pkg-config --libs openblas) 
ODIR = ./build
_OBJs = test.o Matrix.o testlibs.o

OBJs = $(patsubst %.o, $(ODIR)/%.o, $(_OBJs))


main: $(OBJs)
	$(CppC) -o $@ $^ $(LFLAGs)

$(ODIR)/%.o: %.cpp 
	$(CppC) $(CppFLAGs) -o $@ $< 

$(ODIR)/%.o: %.c %.h
	$(CC) -o $@ $< $(CFLAGs)

test: test.cpp
	$(CppC) -o $@ $< 

clean:
	rm ./build/* main

mem:
	valgrind --tool=memcheck --leak-check=full --log-file=./leak.log ./main
