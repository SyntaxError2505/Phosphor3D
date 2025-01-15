#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<fstream>
#include<sstream>
#include<cerrno>

std::string get_file_contents(const char* filename);

class Shader {
public:
	GLint ID;
	Shader(const char* vertexFile, const char* fragmentFile);

	void Activate();
	void Delete();
};

#endif