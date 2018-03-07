SRCs = $(wildcard *cpp)
OBJs = $(patsubst %.cpp, %.o, $(SRCs))

all: $(OBJs)

$(OBJs): %.o: %.cpp
	@echo $(OBJs)
	@mkdir -p $(ODIR)
	$(CPP) $(CFLAGs) $< -o $(ODIR)/$@


# $(OBJs): %.o: %.cpp
#     @echo $(OBJs)
#     $(CPP) -c $< -o /$@
