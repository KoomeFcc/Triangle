window: glfw.o
	g++ -I./ glfw.o -o glfw	-L"./lib" -lglfw3dll -lglew32 -lopengl32 -lglu32 && del glfw.o 

glfw.o: glfw.cpp
	g++ -I./ -c glfw.cpp -L"./lib" -lglfw3dll -lglew32 -lopengl32 -lglu32 


clean:
	del glfw.o


