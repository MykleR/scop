#include <shaders.h>

GL_GENVERTEXARRAYS glGenVertexArrays = NULL;
GL_BINDVERTEXARRAY glBindVertexArray = NULL;
GL_GENBUFFERS glGenBuffers = NULL;
GL_BINDBUFFER glBindBuffer = NULL;
GL_BUFFERDATA glBufferData = NULL;
GL_VERTEXATTRIBPOINTER glVertexAttribPointer = NULL;
GL_ENABLEVERTEXATTRIBARRAY glEnableVertexAttribArray = NULL;
GL_CREATESHADER glCreateShader = NULL;
GL_SHADER_SOURCE glShaderSource = NULL;
GL_COMPILESHADER glCompileShader = NULL;
GL_CREATEPROGRAM glCreateProgram = NULL;
GL_ATTACHSHADER glAttachShader = NULL;
GL_LINKPROGRAM glLinkProgram = NULL;
GL_USEPROGRAM glUseProgram = NULL;
GL_DELETEVERTEXARRAYS glDeleteVertexArrays = NULL;
GL_DELETEBUFFERS glDeleteBuffers = NULL;
GL_DELETEPROGRAM glDeleteProgram = NULL;
GL_DELETESHADER glDeleteShader = NULL;

static bool load_opengl_functions(void)
{
	LOAD_PROC(GL_GENVERTEXARRAYS, glGenVertexArrays);
    LOAD_PROC(GL_BINDVERTEXARRAY, glBindVertexArray);
    LOAD_PROC(GL_GENBUFFERS, glGenBuffers);
    LOAD_PROC(GL_BINDBUFFER, glBindBuffer);
    LOAD_PROC(GL_BUFFERDATA, glBufferData);
    LOAD_PROC(GL_VERTEXATTRIBPOINTER, glVertexAttribPointer);
    LOAD_PROC(GL_ENABLEVERTEXATTRIBARRAY, glEnableVertexAttribArray);
    LOAD_PROC(GL_CREATESHADER, glCreateShader);
    LOAD_PROC(GL_SHADER_SOURCE, glShaderSource);
    LOAD_PROC(GL_COMPILESHADER, glCompileShader);
    LOAD_PROC(GL_CREATEPROGRAM, glCreateProgram);
    LOAD_PROC(GL_ATTACHSHADER, glAttachShader);
    LOAD_PROC(GL_LINKPROGRAM, glLinkProgram);
    LOAD_PROC(GL_USEPROGRAM, glUseProgram);
	return true;
}

GLFWwindow *init_opengl(void)
{
	if (!glfwInit())
		return NULL;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);
	if (!load_opengl_functions()) {
		glfwDestroyWindow(window);
		glfwTerminate();
		return NULL;
	}
	return window;
}
