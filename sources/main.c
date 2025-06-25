#include <scop.h>

int main(void)
{
	GLFWwindow *window;
	if (!(window = init_opengl()))
		return EXIT_FAILURE;

	const char* vertex_shader_src =
		"#version 330 core\n"
		"layout (location = 0) in vec2 pos;\n"
		"void main() { gl_Position = vec4(pos, 1.0, 1.0); }\n";
	const char* fragment_shader_src =
		"#version 330 core\n"
		"out vec4 color;\n"
		"void main() { color = vec4(1.0, 0.0, 0.0, 1.0); }\n";

	// Compile shaders
	GLuint vs = _glCreateShader(GL_VERTEX_SHADER);
	_glShaderSource(vs, 1, &vertex_shader_src, NULL);
	_glCompileShader(vs);

	GLuint fs = _glCreateShader(GL_FRAGMENT_SHADER);
	_glShaderSource(fs, 1, &fragment_shader_src, NULL);
	_glCompileShader(fs);

	GLuint prog = _glCreateProgram();
	_glAttachShader(prog, vs);
	_glAttachShader(prog, fs);
	_glLinkProgram(prog);
	_glUseProgram(prog);

	// Vertex data
	float vertices[] = {
		 0.0f,  0.8f,
		-0.8f, -0.8f,
		 0.8f, -0.8f
	};

	GLuint vao, vbo;
	_glGenVertexArrays(1, &vao);
	_glBindVertexArray(vao);
	_glGenBuffers(1, &vbo);
	_glBindBuffer(GL_ARRAY_BUFFER, vbo);
	_glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	_glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
	_glEnableVertexAttribArray(0);

	// Main loop
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
