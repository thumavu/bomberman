// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
//#include <GL/glew.h>

// Include GLFW
//#include <GLFW/glfw3.h>

#include "Texture.hpp"
#include "common/shader.hpp"
#include "Graphics.hpp"
#include "Window.hpp"

GLFWwindow* window;

int main(void)
{
	Window myWindow;

	myWindow.runGame();
	window = myWindow.getWindow();

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile

	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	//glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	//glClearColor(0.0f, 0.3f, 0.0f, 0.0f);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "TextureFragmentShader.hlsl");

	static const GLfloat g_vertex_buffer_data[] = {
		//vertex data			//texture coordinates 
		-1.0f, 0.9f, 0.0f,		0.0f, 0.0f,
		1.0f, 0.9f, 0.0f,		20.0f, 0.0f,
		1.0f,  1.0f, 0.0f,		20.0f, 1.0f,
		-1.0f, 1.0f, 0.0f,		0.0f, 1.0f,

		0.9f, -1.0f, 0.0f,		0.0f, 1.0f,
		1.0f,  -1.0f, 0.0f,		0.0f, 0.0f,
		0.9f, 0.9f, 0.0f,		20.0f, 1.0f,

		-1.0f, -1.0f, 0.0f,		20.0f, 1.0f,
		0.9f, -0.9f, 0.0f,		0.0f, 0.0f,
		-1.0f, -0.9f, 0.0f,		20.0f, 0.0f,

		-0.9f, -0.9f, 0.0f,		20.0f, 1.0f,
		-0.9f, 0.9f, 0.0f,		0.0f, 1.0f
	};

	GLuint elements[] = {
		0, 1, 2,
		0, 3, 2,
		4, 5, 6,
		5, 1, 6,
		7, 4, 8,
		7, 9, 8,
		9, 10, 11,
		9, 0, 11

	};

	GLuint VertexArrayID, vertexbuffer, elementBuffer, wallTexture;

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	glGenBuffers(1, &vertexbuffer);
	glGenBuffers(1, &elementBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		5 * sizeof(GL_FLOAT),                  // stride
		(void*)0            // array buffer offset
	);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	Texture texture("next.JPEG", &wallTexture);

	//trin declare and init
	GLuint VAOs[96], VBOs[96];//, EBOs[97];
	unsigned int EBOs[96];
	Graphics g(VertexArrayID, VAOs);
	g.setInt(10);

	g.initGlArrays(VBOs, VAOs, EBOs);
	myWindow.setGraphics(g);

	do {
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);
		//bind texture
    	glBindTexture(GL_TEXTURE_2D, wallTexture);
    	g.drawElements();

		//trin logic
		for (int i = 0; i < 96; i++)
		{
			glBindVertexArray(VAOs[i]);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // 3 indices starting at 0 -> 1 triangle
		}

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	// Cleanup VBO
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
