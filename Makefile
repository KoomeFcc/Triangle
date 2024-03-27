window: glfw.o
	g++ -I./ glfw.o functionality.o IndexBuffer.o VertexBuffer.o -o glfw	-L"./lib" -lglfw3dll -lglew32 -lopengl32 -lglu32

glfw.o: glfw.cpp
	g++ -I./ -c glfw.cpp functionality.cpp IndexBuffer.cpp VertexBuffer.cpp -L"./lib" -lglfw3dll -lglew32 -lopengl32 -lglu32 


clean:
	del *.o


