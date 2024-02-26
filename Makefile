window: glfw.o
	g++ -I./ glfw.cpp -o glfw -L"./lib" -lglfw3dll -lglew32 -lopengl32 -lglu32

glfw.o: glfw.cpp
	g++ -I./ -c glfw.cpp -L"./lib" -lglfw3dll -lglew32 -lopengl32 -lglu32


clean:
	del glfw.o


