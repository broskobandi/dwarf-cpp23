PROJECT := game
CC = clang++
CFLAGS = -std=c++23 -stdlib=libc++ -Wall -Wextra -Wunused-result -Wconversion
CPPFLAGS = -Isrc
LDFLAGS = -lSDL2
OS = linux
BUILD_TYPE = debug
STD_CPPM := /usr/lib/llvm/21/share/libc++/v1/std.cppm

BUILD_DIR := build/$(OS)/$(BUILD_TYPE)
OBJ_DIR := $(BUILD_DIR)/obj
SRC_DIR := src

MAIN := $(SRC_DIR)/main.cpp
SRC := $(filter-out $(MAIN), $(wildcard $(SRC_DIR)/*.cpp))
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
MOD := $(wildcard $(SRC_DIR)/*.cppm) $(STD_CPPM)
PCM := $(MOD:$(SRC_DIR)/%.cppm=$(OBJ_DIR)/%.pcm)
MODFLAGS := $(foreach pcm, $(notdir $(basename $(PCM))), -fmodule-file=$(pcm)=$(OBJ_DIR)/$(pcm).pcm)
BIN := $(BUILD_DIR)/$(PROJECT)

.PHONY: all run clean

all: $(BIN)

run: $(BIN)
	./$<

clean:
	rm -rf build

$(BIN): $(MAIN) $(SRC) $(PCM) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(MAIN) $(OBJ) $(MODFLAGS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.pcm: $(MOD) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) --precompile $(MODFLAGS) $< -o $@

$(BUILD_DIR):
	mkdir -p $@

$(OBJ_DIR):
	mkdir -p $@
