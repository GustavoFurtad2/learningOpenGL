#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>

class EBO {

	public:
		// ID reference of EBO object
		GLuint ID;
		// Constructor that generates EBO and link it to indices
		EBO(GLuint* indices, GLsizeiptr size);

		// binds the EBO
		void Bind();
		// unbinds the EBO
		void Unbind();
		// deletes the EBO
		void Delete();

};

#endif