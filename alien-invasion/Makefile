
CXX = g++
CXXFLAGS = -std=c++20 -g -I ./include/ `pkg-config --libs sdl3`

SRC_DIR = ./src
BIN_DIR = ./bin
OUTPUT = $(BIN_DIR)/prog

SRCS = $(wildcard $(SRC_DIR)/*.cpp)

all: $(OUTPUT)

$(OUTPUT): $(SRCS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -rf $(BIN_DIR)


.phony: all clean
