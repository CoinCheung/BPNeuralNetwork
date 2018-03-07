SRCs = $(wildcard ./*cpp)
OBJs = $(patsubst %.cpp, %.o, $(SRCs))


all: $(OBJs)


$(OBJs):%.o:%.cpp
	@mkdir -p $(ODIR)
	$(CPP) $(CFLAGs) $< -o $(ODIR)/$@



