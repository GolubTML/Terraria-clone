all:
	g++ src/*.cpp -o obj/Terraria -lglfw -lGL -ldl -lpthread -lX11 -lGLEW


make run:
	./obj/Terraria