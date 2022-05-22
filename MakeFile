CC = g++
#define SDL_MAIN_HANDLED
LINKFLAGS = -Lsrcgame/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
INCLUDE_DIR = -Isrcgame/include
COMPILE_FLAGS = -Wall -c $(INCLUDE_DIR)
SOURCE = 
BUILD_FLAG = $(LINKFLAGS)
OBJ_FILES = $(patsubst %.cpp, %.o, $(wildcard *.cpp))


all: build run

rebuild: clean build

build: program

program: $(OBJ_FILES)
	$(CC) $^ $(BUILD_FLAG) -o $@

$(OBJ_FILES): %.o : %.cpp
	$(CC) $(COMPILE_FLAGS) $< -o $@

%.cpp: %.h
	@echo $<
run:
	program

clean:
	rm -f bin/*
 


