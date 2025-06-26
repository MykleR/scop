#include "debug.h"
#include "shaders.h"
#include <scop.h>

int main(void)
{
	GLFWwindow *window = init_opengl();
	if (__builtin_expect(window == NULL, 0))
		return EXIT_FAILURE;
	LOG_OK("OpenGL initialized successfully");

	// Compile shaders
	GLuint program;
	if (shader_program(VERTEX_SSRC, FRAGMENT_SSRC, &program) == ERR_CODE)
	{
		LOG_ERR("Failed to create shader program");
		glfwDestroyWindow(window);
		glfwTerminate();
		return EXIT_FAILURE;
	} LOG_OK("Shader program created successfully");

	// Vertex data
	float vertices[] = {
		// positions       // colors        // tex coords
		 1.0f, -1.0f, 0.0f,  1, 0, 0,        1, 0,
		-1.0f, -1.0f, 0.0f,  0, 1, 0,        0, 0,
		 0.0f,  1.0f, 0.0f,  0, 0, 1,        0.5, 1
	};

	GLuint vao, vbo;
	_glGenVertexArrays(1, &vao);
	_glBindVertexArray(vao);
	_glGenBuffers(1, &vbo);
	_glBindBuffer(GL_ARRAY_BUFFER, vbo);
	_glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	// position
    _glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    _glEnableVertexAttribArray(0);
    // color
    _glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    _glEnableVertexAttribArray(1);
    // texcoord
    _glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    _glEnableVertexAttribArray(2);
	_glUseProgram(program);

	// Main loop
	while (!glfwWindowShouldClose(window)) {
		_glUniform1f(_glGetUniformLocation(program, "iTime"), (int)glfwGetTime() % 60); 
		glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, 1);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
