#include <OpenglApp.hpp>

OpenglApp::OpenglApp() : _window(nullptr) {}

OpenglApp::~OpenglApp()
{
	if (_window) {
		glfwDestroyWindow(_window);
		glfwTerminate();
	}
}

void OpenglApp::initOpengl()
{
	if (!glfwInit())
		throw GLFWInitException();
	LOG_OK("GLFW initialized successfully");

	_window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE, nullptr, nullptr);
	if (!_window)
		throw WindowInitException();
	glfwMakeContextCurrent(_window);
	LOG_OK("Window initialized successfully");

	if (glewInit() != GLEW_OK)
		throw GLEWInitException();
	LOG_OK("GLEW initialized successfully");
}

void OpenglApp::initShader()
{
	try {
		_shaders = Pipeline();
		_shaders.addShader(GL_VERT_SHADER, GL_VERTEX_SHADER);
		_shaders.addShader(GL_FRAG_SHADER, GL_FRAGMENT_SHADER);
		_shaders.linkProgram();
	} CATCH_RET();
	LOG_OK("Shaders initialized successfully");
}

void OpenglApp::loop()
{
	// Vertex data
	float vertices[] = {
		// positions       // colors        // tex coords
		 1.0f, -1.0f, 0.0f,  1, 0, 0,        1, 0,
		-1.0f, -1.0f, 0.0f,  0, 1, 0,        0, 0,
		 0.0f,  1.0f, 0.0f,  0, 0, 1,        0.5, 1
	};

	GLuint vao, vbo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	// position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texcoord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
	glUseProgram(_shaders.get_id());
	while (!glfwWindowShouldClose(_window))
	{
		glfwPollEvents();
		if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(_window, true);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(_window);
	}
}

int OpenglApp::run() {
	try {
		initOpengl();
		initShader();
		loop();
	} CATCH_RET(EXIT_FAILURE);
	return EXIT_SUCCESS;
}
