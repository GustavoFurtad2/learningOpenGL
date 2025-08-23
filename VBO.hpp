#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>

class VBO {

	public:
		// ID reference of VBO object
		GLuint ID;
		// Constructor that generates a VBO and link it to vertices
		VBO(GLfloat* vertices, GLsizeiptr size);

		// binds the VBO
		void Bind();
		// unbinds the VBO
		void Unbind();
		// deletes the VBO
		void Delete();

};

#endif