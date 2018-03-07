CPP = g++
ROOT = $(shell pwd)
CFLAGs = -c -I$(ROOT)/Matrix -I$(ROOT)/Math -I$(ROOT)/Layers -std=c++11 
LFLAGs = -lm -ltcmalloc


SUBDIRs = ./Matrix ./Math ./Layers
ODIR = $(ROOT)/build
CURR_SRCs = $(wildcard *.cpp)
CURR_OBJs = $(patsubst %.cpp, %.o, $(CURR_SRCs))
OBJs = $(wildcard $(ODIR)/*.o)

export CPP CFLAGs ROOT ODIR 


main: $(CURR_OBJs) $(SUBDIRs) 
	@echo $(CURR_OBJs)
	$(CPP) $(OBJs) -o $@ $(LFLAGs)

$(CURR_OBJs):%.o: %.cpp
	@mkdir -p $(ODIR)
	$(CPP) -o $(ODIR)/$@ $< $(CFLAGs)

$(SUBDIRs)::
	$(MAKE) -C $@




clean:
	rm -rf main $(ODIR) 

