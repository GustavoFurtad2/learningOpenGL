#include<iostream>

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include "shaderClass.hpp"

#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"

// Vertices coordinates
GLfloat vertices[] = {

	// coordinates                               / colors
	-0.5f,  -0.5f * float(sqrt(3)) / 3,    0.0f,  0.8f, 0.3f,  0.02f, // Lower left corner
	0.5f,   -0.5f * float(sqrt(3)) / 3,    0.0f,  0.8f, 0.3f,  0.02f, // Lower right corner
	0.0f,   0.5f * float(sqrt(3)) * 2 / 3, 0.0f,  1.0f, 0.6f,  0.032f, // Upper corner

	-0.25f, 0.5f * float(sqrt(3)) / 6,     0.0f,  0.9f, 0.45f, 0.17f, // Inner left
	0.25f,  0.5f * float(sqrt(3)) / 6,     0.0f,  0.9f, 0.45f, 0.17f, // Inner right
	0.0f,  -0.5f * float(sqrt(3)) / 3,     0.0f,  0.8f, 0.3f,  0.02f, // Inner Down
};

// indices for vertices order
GLuint indices[] = {
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper mid triangle
};

int main() {

	// initialize glfw
	glfwInit();

	// tell glfw what version of OpenGL we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// tell glfw we are using the CORE profile
	// so that means we only have the modern functions
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// create a glfw window object of 800x600 pixels, naming it "Learning OpenGL"
	GLFWwindow* window = glfwCreateWindow(800, 600, "Learning OpenGL", NULL, NULL);
	// error check if the windows falls to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// introduce the window into the current context
	glfwMakeContextCurrent(window);

	// load GLAD so its configures OpenGL
	gladLoadGL();
	// specify the viewport of OpenGL in the Window
	// in this case the viewport goes from x = 0, y = 0, to x = 800, y = 600
	glViewport(0, 0, 800, 600);

	// generate shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// generates VAO(vertex array object) and binds it
	VAO VAO1;
	VAO1.Bind();

	// generates VBO(vertex buffer object) and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// generates EBO(element buffer object) and links it to indices
	EBO EBO1(indices, sizeof(indices));
	// links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*) 0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*) (3 * sizeof(float)));
	// unbind all to prevent accidentally modifying tem
	VAO1.Unbind();

	VBO1.Bind();

	EBO1.Unbind();

	// gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
	
	// main while loop
	while (!glfwWindowShouldClose(window))
	{
		// specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		// assigns a value to the uniform; NOTE: must always be done after activating the Shader Program
		glUniform1f(uniID, 0.25f);
		// bind the VAO so OpenGL knows to use it

		VAO1.Bind();

		// draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// take care of all GLFW events
		glfwPollEvents();
	}


	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();

	return 0;
}