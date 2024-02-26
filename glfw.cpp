#include <windows.h>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>

unsigned int buffer;
GLint size;
float positions[6] = {
	-0.2f, -0.2f,
	0.0f, 0.2f,
	0.2f, -0.2f
};

static unsigned int CompileShader(unsigned int type, const std::string& source){

	unsigned int id = glCreateShader(GL_VERTEX_SHADER);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE){
	
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failes to  compile shader" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")<<
				std::endl << message << std::endl;
		glDeleteShader(id);
		return 0;
	}
	return id;
}

static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader){	
	unsigned int program = glCreateProgram();
	unsigned int  vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void Keypressed(GLFWwindow* window, int key, int scancode, int action, int mods);
void Buffered(unsigned int *buffer);
void Keytest(GLFWwindow* window);

int main(void)
{
	GLFWwindow* window;

	if (!glfwInit())
		return -1;	
	
	window = glfwCreateWindow(1024, 768, "new test window", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if(glewInit() != GLEW_OK)
		std::cout << "Error" << std::endl;	

	//functions called to buffer
	Buffered(&buffer);
	
	std::cout << "To movo the triangle:" << std::endl
		<< "UP ARROW to go up" << std::endl
		<< "RIGHT ARROW to go right" << std::endl
		<< "LEFT ARROW to go left" << std::endl
		<< "DOWN ATTOW to go dowm\n" << std::endl
		<< "Press W to scale the triangle" << std::endl
		<< "Press S to descale it" << std::endl << "PRESS A or E to shade it" << std::endl;

	/*std::string vertexShader =
		"#version 330 core\n"
		"layout(location = 0) in vec4 position;\n"
		"void main(){\n"
			"gl_Position = position;\n"
		"}\n";

	std::string fragmentShader = 
		"#version 330 core\n"
		"layout(location = 0) out vec4 color;\n"
		"void main(){\n"
			"color = vec4(1.0, 0.0, 0.0, 1.0);\n"
		"}\n";

	unsigned int Shader = CreateShader(vertexShader, fragmentShader);
	glUseProgram(Shader);*/

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		//glBegin(GL_TRIANGLES);
		//if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
 		//	Biggertri();
		//	Buffered(&buffer); 
		//	Sleep(60);
		//}

		//glfwSetKeyCallback(window, Keypressed);
		Keytest(window);

		glDrawArrays(GL_TRIANGLES, 0, 3);
	
		//glDrawElements(GL_TRIANGLES, 3, GL_ARRAY_BUFFER, NULL);
		//glVertex2f(-0.5f, -0.5f);
		//glVertex2f(0.0f, 0.5f);
		//glVertex2f(0.5f, -0.5f);

		//glEnd();

		glfwSwapBuffers(window);

		glfwPollEvents();

		Sleep(5);
	}
	glfwTerminate();
	return 0;
} 

void Buffered(unsigned int *buffer) {

	size = 0;
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

	if((6 * sizeof(float)) == size){
			glDeleteBuffers(1, buffer);
		}

	glGenBuffers(1, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, *buffer); //Bind elements to be drawm
	glEnableVertexAttribArray(0);
	glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW); 


	return;
}

void Keytest(GLFWwindow* window){

	int k = GLFW_PRESS;
	int keyu = glfwGetKey(window, GLFW_KEY_UP);
	int keyd = glfwGetKey(window, GLFW_KEY_DOWN);
	

	if (keyu == GLFW_PRESS or keyd == GLFW_PRESS) {
		for (int i = 1; i < 6; i += 2) positions[i] += keyu == k ? 0.024f : -0.024f;
		Buffered(&buffer);
		return;
	}

	int keyr = glfwGetKey(window, GLFW_KEY_RIGHT);
	int keyl = glfwGetKey(window, GLFW_KEY_LEFT);

	if(keyr == GLFW_PRESS or keyl == GLFW_PRESS){
		for (int i = 0; i < 6; i += 2) positions[i] += keyr == k ? 0.024f : -0.024f;
		Buffered(&buffer);
		return;
	}

	int keyw = glfwGetKey(window, GLFW_KEY_W);
	int keys = glfwGetKey(window, GLFW_KEY_S);

	if( keyw == GLFW_PRESS or keys == GLFW_PRESS){

		for (int i = 0; i < 6; i++){
			if (positions[i] == 0.0f) continue;
			if (keyw == k) positions[i] *= 1.024f; 
			if (keys == k) positions[i] *= 0.976f;
		}
		Buffered(&buffer);
		return;
	}

	int keyD = glfwGetKey(window, GLFW_KEY_D);
	int keya = glfwGetKey(window, GLFW_KEY_A);

	if(keyD == GLFW_PRESS or keya == GLFW_PRESS){

		positions[2] += keyD == k ? 0.024f : -0.024f;
		Buffered(&buffer);
		return;
	}

	return;
}

/*void Keypressed(GLFWwindow* window, int key, int scancode, int action, int mods){

	if ((key == GLFW_KEY_W or key == GLFW_KEY_S) && action == GLFW_PRESS){
		for (int i = 0; i < 6; i++){
			if (positions[i] == 0.0f) continue;
			if (key == GLFW_KEY_W) positions[i] *= 1.10f; 
			if (key == GLFW_KEY_S) positions[i] *= 0.90f;
			//std::cout << positions[i] << std::endl;
		}
	}else if((key == GLFW_KEY_DOWN or key == GLFW_KEY_UP) && (action == GLFW_REPEAT or action == GLFW_PRESS)){
		
		for (int i = 1; i < 6; i += 2) positions[i] += key == GLFW_KEY_UP? 0.1f : -0.1f;

	}else if((key == GLFW_KEY_RIGHT or key == GLFW_KEY_LEFT)&& (action == GLFW_REPEAT or action == GLFW_PRESS)){

		for (int i = 0; i < 6; i += 2) positions[i] += key == GLFW_KEY_LEFT? -0.1f : 0.1f;

	}
	Buffered(&buffer);
}*/

