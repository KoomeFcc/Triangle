#include "include/functionality.h"

float positions[12] = {
	-0.5f, -0.5f,
	0.5f, -0.5f,
	0.5f, 0.5f,
	-0.5f, 0.5f
};
unsigned int indices[] = { 0, 1, 2, 2, 3, 0 }; //unsigned int buffer; unsigned int ibo;

void Buffered(unsigned int *buffer, unsigned int *ibo, unsigned int *vao) {

	glBindVertexArray(*vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, *buffer); //Bind elements to be drawm
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW); 
	glEnableVertexAttribArray(0);
	glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0); //link buffer and vao

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	return;
}

void Keytest(GLFWwindow* window){
//TODO: find function to make sin and cos operations to fix rotation
	int k = GLFW_PRESS;
	int keyu = glfwGetKey(window, GLFW_KEY_UP);
	int keyd = glfwGetKey(window, GLFW_KEY_DOWN);

	if (keyu == GLFW_PRESS or keyd == GLFW_PRESS) {
		for (int i = 1; i < 12; i += 2) positions[i] += keyu == k ? 0.024f : -0.024f;
		Buffered(&buffer, &ibo, &vao);
		return;
	}

	int keyr = glfwGetKey(window, GLFW_KEY_RIGHT);
	int keyl = glfwGetKey(window, GLFW_KEY_LEFT);

	if(keyr == GLFW_PRESS or keyl == GLFW_PRESS){
		for (int i = 0; i < 12; i += 2) positions[i] += keyr == k ? 0.024f : -0.024f;
		Buffered(&buffer, &ibo, &vao);
		return;
	}

	int keyw = glfwGetKey(window, GLFW_KEY_W);
	int keys = glfwGetKey(window, GLFW_KEY_S);

	if( keyw == GLFW_PRESS or keys == GLFW_PRESS){

		for (int i = 0; i < 12; i++){
			if (positions[i] == 0.0f) continue;
			if (keyw == k) positions[i] *= 1.024f; 
			if (keys == k) positions[i] *= 0.976f;
		}
		Buffered(&buffer, &ibo, &vao);
		return;
	}

	int keya = glfwGetKey(window, GLFW_KEY_A);
	int keyD = glfwGetKey(window, GLFW_KEY_D);

	if( keya == GLFW_PRESS or keyD == GLFW_PRESS){
	
		positions[2] += keyD == k ? 0.024f : -0.024f;
		Buffered(&buffer, &ibo, &vao);
		return;
	}

	int keyQ = glfwGetKey(window, GLFW_KEY_Q);
	int keyE = glfwGetKey(window, GLFW_KEY_E);
	float a = 0.0f; float b = 0.0f;
	struct rotaa { float x, y; }; struct rotab { float x, y;};
	rotaa rota; rotab rotb;

	if( keyQ == GLFW_PRESS or keyE == GLFW_PRESS){

		for ( int i = 0; i < 12; i+=2){
			
			b = positions[i];
			a = positions[i + 1];
			rota.x = (b * 0.9659f) + (a * -0.2588f); rota.y = (b * 0.2588f) + (a * 0.9659f);
			rotb.x = (b * 0.9659f) + (a * 0.2588f) ; rotb.y = (b * -0.2588f) + (a * 0.9659f);  
			positions[i] = keyQ == k ? rota.x : rotb.x;
			positions[i + 1] = keyQ == k ? rota.y : rotb.y;	
		}
		Buffered(&buffer, &ibo, &vao);
		return;
	}
	return;
}

void GLClearError(){
	while(glGetError() != GL_NO_ERROR); //Call function until no error
}

void GLCheckError(){
	while(GLenum error = glGetError()){
		std::cout << "[OpenGl Error] (" << error << ")" << std::endl;
	}
}

ShaderProgramSource ParseShader(const std::string& filepath){

	std::ifstream stream(filepath);

	enum class ShaderType{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while(getline(stream, line)){
	
		if(line.find("#shader") != std::string::npos)
		{
			if(line.find("vertex") != std::string::npos) //set mode to vertex
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)   //set mode to fragment
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}
	return {ss[0].str(), ss[1].str()};
}

unsigned int CompileShader(unsigned int type, const std::string& source){

	unsigned int id = glCreateShader(type);
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

int CreateShader(const std::string& vertexShader, const std::string& fragmentShader){	
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

void printControls(){

	std::cout << "To move the triangle:" << std::endl << "UP ARROW to go up" << std::endl
		<< "RIGHT ARROW to go right" << std::endl << "LEFT ARROW to go left" << std::endl
		<< "DOWN ATTOW to go dowm\n" << std::endl << "Press W to scale the triangle" << std::endl
		<< "Press S to descale it" << std::endl << "PRESS A or D to shade it" << std::endl
		<< "Press A and E to rotate it" << std::endl << "\n";

}
