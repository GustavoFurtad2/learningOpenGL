#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_files_contents(const char* filename);

class Shader {

	public:
		// reference ID of the shader program
		GLuint ID;
		// constructor that build the shader program from 2 different shaders
		Shader(const char* vertexFile, const char* fragmentFile);

		// activates the shader program
		void Activate();
		// deletes the shader program
		void Delete();

	private:

		// checks if the different shaders have compiled properly
		void compileErrors(unsigned int shader, const char* type);

};

#endif