#include <scop.h>

int main(void)
{
	GLFWwindow *window;
	if (!(window = init_opengl()))
		return EXIT_FAILURE;

	const char* vertex_shader_src =
		"#version 330 core\n"
		"layout (location = 0) in vec2 pos;\n"
		"void main() { gl_Position = vec4(pos, 0.0, 1.0); }\n";
	const char* fragment_shader_src =
		"#version 330 core\n"
		"out vec4 color;\n"
		"void main() { color = vec4(1.0, 0.0, 0.0, 1.0); }\n";

	// Compile shaders
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader_src, NULL);
	glCompileShader(vs);

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader_src, NULL);
	glCompileShader(fs);

	GLuint prog = glCreateProgram();
	glAttachShader(prog, vs);
	glAttachShader(prog, fs);
	glLinkProgram(prog);

	// Vertex data
	float vertices[] = {
		 0.0f,  0.8f,
		-0.8f, -0.8f,
		 0.8f, -0.8f
	};

	GLuint vao, vbo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
	glEnableVertexAttribArray(0);

	// Main loop
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(prog);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
