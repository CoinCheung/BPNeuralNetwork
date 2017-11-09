CppC = g++
CFLAGs = -c -g -std=c++11
LFLAGs = -lm -ltcmalloc -lopenblas
ODIR = ./build
_OBJs = main.o BP.o Matrix.o

OBJs = $(patsubst %.o, $(ODIR)/%.o, $(_OBJs))


main: $(OBJs) 
	$(CppC) -o $@ $(LFLAGs) $^ 

$(ODIR)/%.o: %.cpp
	$(CppC) -o $@ $< $(CFLAGs)


clean:
	rm main $(ODIR)/*

