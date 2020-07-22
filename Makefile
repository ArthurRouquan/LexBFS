CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++2a -ggdb -O3

BIN		:= bin
SRC		:= src
INCLUDE	:= include

EXECUTABLE	:= main


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@

clean:
	-rm $(BIN)/*
