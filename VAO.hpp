#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>
#include "VBO.hpp"

class VAO {

	public:
		// ID reference of VAO object
		GLuint ID;
		// Constructor that generates a VAO ID
		VAO();

		// Links a VBO attribute such as a position or color to the VAO
		void LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
		// binds the VAO
		void Bind();
		// unbinds the VAO
		void Unbind();
		// deletes the VAO
		void Delete();
};

#endif