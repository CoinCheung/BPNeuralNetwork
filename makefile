CppC = g++
CFLAGs = -c -g -std=c++11
LFLAGs = -lm -ltcmalloc -lopenblas
ODIR = ./build
_OBJs = main.o Matrix.o numeric.o BP.o

OBJs = $(patsubst %.o, $(ODIR)/%.o, $(_OBJs))


main: $(OBJs) 
	$(CppC) -o $@ $(LFLAGs) $^ 

$(ODIR)/%.o: %.cpp
	@mkdir -p $(ODIR)
	$(CppC) -o $@ $< $(CFLAGs)


clean:
	rm -rf main $(ODIR) 

