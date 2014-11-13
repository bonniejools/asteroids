#include <iostream>
#include <cmath>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <thread>
#include <SOIL/SOIL.h>
#include <math.h>

#include "loadshaders.h"
#include "main.h"

GLfloat spaceshipVertices[] = {
//  x       y
	 0.0f,   0.125f,
	-0.125f, -0.125f,
	 0.0f,  -0.0625f,
	 0.125f, -0.125f,
};

GLfloat asteroidVertices[] = {
//  x       y
	 0.5f,   0.125f,
	 0.375f, -0.125f,
	 0.5f,  -0.0625f,
	 0.625f, -0.125f,
};

GLuint spaceshipElements[] = {
	0, 1,
	1, 2,
	2, 3,
	3, 0
};

int main()
{
	using namespace std;

	// Creates the GLFW context.
	// GLFW creates a window with an OpenGL context.
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow* window = glfwCreateWindow(WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_TITLE, nullptr,
		nullptr);
	glfwMakeContextCurrent(window);

	// GLEW links to gpu functions
	glewExperimental = GL_TRUE;
	glewInit();

	// Loads vertex & fragment shaders
	GLuint program = LoadShader(VERTEX_SHADER_LOCATION,
		FRAGMENT_SHADER_LOCATION);
	glUseProgram(program);

	// Create a Vertex Array Object. The Vertex Array Object gives information
	// about how the vertices are stored. once bound, glEnableVertexAttribArray()
	// will pass information on how the vertices are arranged and what data is
	// where. This allows the shaders to use the data without having to work out
	// what it is first.
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create a Vertex Buffer Object which will contain all the vertex data.
	// Remember that the vertices have no information stored about them and
	// so you will need an element buffer to link all the vertices.
	// glGenBuffers() will assign vbo an object buffer name so that it can
	// be referenced.
	GLuint vbo[2];
	glGenBuffers(2, vbo);
	// Make vbo the current object with glBindBuffer() and then 'upload' data to it.
	// GL_STATIC_DRAW means that the vertex data will be uploaded once and then
	// drawn lots and lots of times.
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(spaceshipVertices), spaceshipVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(asteroidVertices), asteroidVertices, GL_STATIC_DRAW);


	// Create an element buffer. This will allow the vertices to be grouped into
	// triangles.
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(spaceshipElements),
		spaceshipElements, GL_STATIC_DRAW);

	// The vertex data is useless if the shaders don't know what it all is. The
	// VAO stores data on what all the vertices mean but it needs to be told
	// before it is useful. Here, I will find references to the various vec*s
	// defined in the fragment shader and then describe where that information
	// is stored. This meta information is stored in the Vertex Array Object.	
	GLint posAttrib = glGetAttribLocation(program, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE,
		2*sizeof(float), 0);



	while(!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
		// Close window if 'esc' key is pressed

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);

		// Clear the screen to black
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, 0);
		
	}

	glfwTerminate();
	return 0;
}