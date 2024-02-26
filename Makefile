window: glfw.o
	g++ -I./ glfw.cpp -o glfw -L"C:\Users\HeRnAn\Desktop\VsCode\Triangle\lib" -lglfw3dll -lglew32 -lopengl32 -lglu32

glfw.o: glfw.cpp
	g++ -I./ -c glfw.cpp -L"C:\Users\HeRnAn/Desktop/VsCode/Triangle/lib" -lglfw3dll -lglew32 -lopengl32 -lglu32


clean:
	del glfw.o


