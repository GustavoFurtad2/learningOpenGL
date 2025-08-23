#include "shaderClass.hpp"

std::string get_file_contents(const char* filename) {

	std::ifstream in(filename, std::ios::binary);

	if (in) {

		std::string contents;

		in.seekg(0, std::ios::end);

		contents.resize(in.tellg());

		in.seekg(0, std::ios::beg);

		in.read(&contents[0], contents.size());

		in.close();

		return contents;
	}

	throw(errno); 
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {

	// read vertexFile and fragmentFile and store the strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// convert the shader source strings into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// create VAO and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// attach vertex shader source to the VAO
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// compilete the vertex shader into machine code
	glCompileShader(vertexShader);
	// checks if shader compiled sucessfully
	compileErrors(vertexShader, "VERTE");

	// create fragment shader object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// attach fragment shader source to the fragment shader object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// compile the vertex shader into machine code
	glCompileShader(fragmentShader);
	// check if shader compiled sucessfully
	compileErrors(fragmentShader, "FRAGMENT");

	// create shader program object and get its reference
	ID = glCreateProgram();
	// attach the verte and fragment shaders to the shader program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// wrap-up/link all the shaders together into the shader program
	glLinkProgram(ID);
	// check if shaders linked sucessfully
	compileErrors(ID, "PROGRAM");

	// delete the now useless vertex and fragment shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

// activates the shader program
void Shader::Activate() {

	glUseProgram(ID);
}

// deletes the shader program
void Shader::Delete() {

	glDeleteProgram(ID);
}

// check if the different shaders have compiled properly
void Shader::compileErrors(unsigned int shader, const char* type) {

	// stores status of compilation
	GLint hasCompiled;
	// character array to store error message in
	char infoLog[1024];

	if (type != "PROGRAM") {

		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);

		if (hasCompiled == GL_FALSE) {

			glGetShaderInfoLog(shader, 1024, NULL, infoLog);

			std::cout << "SHADER_COMPILATION_ERROR for: " << type << "\n" << std::endl;
		}
	}
	else {

		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);

		if (hasCompiled == GL_FALSE) {

			glGetProgramInfoLog(shader, 1025, NULL, infoLog);

			std::cout << "SHADER_LINKING_ERROR for: " << type << "\n" << std::endl;
		}
	}
}