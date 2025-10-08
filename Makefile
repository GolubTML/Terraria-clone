all:
	g++ src/*.cpp src/imgui/imgui*.cpp -o obj/Terraria -lglfw -lGL -ldl -lpthread -lX11 -lGLEW -Iimgui

make run:
	./obj/Terraria