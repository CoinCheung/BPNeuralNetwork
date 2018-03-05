CC = gcc
CFLAGs = -g -c -std=c99
LFLAGs = -lm -lopenblas -ltcmalloc
BUILD_DIR = ./build
_OBJs = test.o BP.o numeric.o Matrix.o

OBJs = $(patsubst %.o, $(BUILD_DIR)/%.o, $(_OBJs))

main: $(OBJs)
	$(CC) -o $@ $^ $(LFLAGs)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGs) $< -o $@

clean:
	rm ./$(BUILD_DIR) main test
