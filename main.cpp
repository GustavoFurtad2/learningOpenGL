#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() {

	// initialize glfw
	glfwInit();

	// tell glfw what version of OpenGL we are using
	// OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// tell glfw we are using the core profile(also we have the compatibility profile)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create the window
	GLFWwindow* window = glfwCreateWindow(800, 600, "Learning OpenGL Part 1 - Window", NULL, NULL);

	// error check if the windows failed to create
	if (window == NULL) {

		std::cout << "Failed to create GLFW window" << std::endl;

		glfwTerminate();

		return -1;
	}

	// introduce the window into the curret context
	glfwMakeContextCurrent(window);

	// load glad for configure OpenGL
	gladLoadGL();
	
	// specify the viewport of OpenGL in the Window
	// set viewport from (0, 0) to (800, 600)
	glViewport(0, 0, 800, 600);

	// specify the background color
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// clean the back buffer and assig the new color to it
	glClear(GL_COLOR_BUFFER_BIT);
	// swap the back buffer with the front buffer
	glfwSwapBuffers(window);

	// main while loop
	while (!glfwWindowShouldClose(window)) {
		// take care of all glfw events
		glfwPollEvents();
	}
	
	// delete window before ending the program
	glfwDestroyWindow(window);
	// termiate glfw before ending the program
	glfwTerminate();

	return 0;
}