all:
	g++ src/*.cpp src/ImGui/*.cpp src/ImGui/backends/*.cpp -o obj/Terraria -lglfw -lGL -ldl -lpthread -lX11 -lGLEW


make run:
	./obj/Terraria