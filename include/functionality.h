#include <windows.h>
#include "../GL/glew.h"
#include "../GLFW/glfw3.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>	

extern float positions[12];
extern unsigned int indices[6];
extern unsigned int buffer;
extern unsigned int ibo;
extern GLint size;
extern GLint sizeibo;

struct ShaderProgramSource{
	std::string VertexSource;
	std::string FragmentSource;
};

ShaderProgramSource ParseShader(const std::string& filepath);
unsigned int CompileShader(unsigned int type, const std::string& source);
int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
void Keypressed(GLFWwindow* window, int key, int scancode, int action, int mods);
void Buffered(unsigned int *buffer, unsigned int *ibo);
void Keytest(GLFWwindow* window);
void printControls();

