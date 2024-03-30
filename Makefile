CC = g++
LANG_STD = -std=c++17
COMPILER_FLAGS = -Wall -Wfatal-errors
INCLUDE_PATH = -I"./libs/"
SRC_FILES = ./src/*.cpp \
	./src/Game/*.cpp \
	./src/Logger/*.cpp \
	./src/ECS/*.cpp \
	./src/AssetStore/*.cpp \
	./libs/imgui/*.cpp
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua5.3 
OBJ_NAME = gameengine

.PHONY : deps build all run clean

all: deps build

deps:
	sudo apt update 
	sudo apt install libsdl2-dev libsdl2-2.0-0 libjpeg-dev libwebp-dev libtiff5-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-image-2.0-0 libglm-dev libsdl2-mixer-dev liblua5.3-dev -y 

build:
	$(CC) $(COMPILER_FLAGS) $(LANG_STD) $(INCLUDE_PATH) $(SRC_FILES) $(LINKER_FLAGS) -o $(OBJ_NAME)

run:
	./$(OBJ_NAME)

clean:
	rm $(OBJ_NAME)


