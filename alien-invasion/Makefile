
CXX = g++
CXXFLAGS = -std=c++20 -g -I ./include/ `pkg-config --libs sdl3`

SRC_DIR = ./src
BIN_DIR = ./bin
OUTPUT = $(BIN_DIR)/prog


SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%.o, $(SRCS))

all: $(OUTPUT)

$(OUTPUT): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN_DIR)


.phony: all clean
