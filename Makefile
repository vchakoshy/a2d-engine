build:
	g++ src/*.cpp -o gameengine.out -lSDL2 -lSDL2_image

run:
	./gameengine.out