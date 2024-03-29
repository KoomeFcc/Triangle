#include "include/functionality.h"

unsigned int buffer, ibo, vao;

int main(void)
{
	GLFWwindow* window;

	if (!glfwInit())
		return -1;	
	
	window = glfwCreateWindow(640, 480, "new test window", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if(glewInit() != GLEW_OK)
		std::cout << "Error" << std::endl;	

	//functions called to buffer
	glGenBuffers(1, &buffer); glGenBuffers(1, &ibo); glGenVertexArrays(1, &vao);
	Buffered(&buffer, &ibo, &vao);
	
	printControls();

	ShaderProgramSource source = ParseShader("./res/shaders/Basic.shader");
	
	unsigned int Shader = CreateShader(source.VertexSource, source.FragmentSource);
	glUseProgram(Shader);

	int location = glGetUniformLocation(Shader, "u_Color");
	if (location == -1) std::cout << "[Uniform not finded]" << std::endl;
	glUniform4f(location, 0.8, 0.3f, 0.8f, 1.0f);

	glBindVertexArray(0);
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	float r = 0.5f; float increment = 0.025f; //TODO: put changing coloring into function
	
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		//glfwSetKeyCallback(window, Keypressed);
		Keytest(window);
	
		glUseProgram(Shader);
		glUniform4f(location, r, 0.1f, 0.3f, 1.0f); //defined the uniform
							    
		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		//GLClearError(); //check if error was raised during earlier function call
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		//GLCheckError(); //check if error is raised during Draw call

		if (r > 1.0f) increment = -0.025f;
		else if (r < 0.0f) increment = 0.025f;
		r += increment;

		glfwSwapBuffers(window);

		glfwPollEvents();

		//Sleep(5);
	}
	glDeleteProgram(Shader);
	glfwTerminate();
	return 0;
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

