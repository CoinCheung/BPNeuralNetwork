CPP = g++
CFLAGs = -c -std=c++11
LFLAGs = -lm -ltcmalloc -lopenblas 
ODIR = ./build
_OBJs = main.o numeric.o BP.o
MDIR = ./Matrix
_MOBJs = Matrix.o 


OBJs = $(patsubst %.o, $(ODIR)/%.o, $(_OBJs)) 
OBJs += $(patsubst %.o, $(MDIR)/%.o, $(_MOBJs)) 


main: $(OBJs) 
	$(CPP) $^ $(LFLAGs) -o $@  

$(ODIR)/%.o: %.cpp
	@mkdir -p $(ODIR)
	$(CPP) -o $@ $< $(CFLAGs)


clean:
	rm -rf main $(ODIR) 

