#include <GLFW/glfw3.h>
#include <shaders.h>

PFNGLCREATESHADERPROC				_glCreateShader = NULL;
PFNGLSHADERSOURCEPROC				_glShaderSource = NULL;
PFNGLCOMPILESHADERPROC				_glCompileShader = NULL;
PFNGLCREATEPROGRAMPROC				_glCreateProgram = NULL;
PFNGLATTACHSHADERPROC				_glAttachShader = NULL;
PFNGLLINKPROGRAMPROC				_glLinkProgram = NULL;
PFNGLUSEPROGRAMPROC					_glUseProgram = NULL;
PFNGLGENVERTEXARRAYSPROC			_glGenVertexArrays = NULL;
PFNGLBINDVERTEXARRAYPROC			_glBindVertexArray = NULL;
PFNGLGENBUFFERSPROC					_glGenBuffers = NULL;
PFNGLBINDBUFFERPROC					_glBindBuffer = NULL;
PFNGLBUFFERDATAPROC					_glBufferData = NULL;
PFNGLVERTEXATTRIBPOINTERPROC		_glVertexAttribPointer = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC	_glEnableVertexAttribArray = NULL;
PFNGLDELETEVERTEXARRAYSPROC			_glDeleteVertexArrays = NULL;
PFNGLDELETEBUFFERSPROC				_glDeleteBuffers = NULL;
PFNGLDELETEPROGRAMPROC				_glDeleteProgram = NULL;
PFNGLDELETESHADERPROC				_glDeleteShader = NULL;

static bool load_opengl_functions(void)
{
	LOAD_PROC(PFNGLGENBUFFERSPROC, _glGenBuffers, glGenBuffers);
	LOAD_PROC(PFNGLBINDBUFFERPROC, _glBindBuffer, glBindBuffer);
	LOAD_PROC(PFNGLBUFFERDATAPROC, _glBufferData, glBufferData);
	LOAD_PROC(PFNGLUSEPROGRAMPROC, _glUseProgram, glUseProgram);
	LOAD_PROC(PFNGLLINKPROGRAMPROC, _glLinkProgram, glLinkProgram);
	LOAD_PROC(PFNGLCREATESHADERPROC, _glCreateShader, glCreateShader);
	LOAD_PROC(PFNGLDELETESHADERPROC, _glDeleteShader, glDeleteShader);
	LOAD_PROC(PFNGLSHADERSOURCEPROC, _glShaderSource, glShaderSource);
	LOAD_PROC(PFNGLATTACHSHADERPROC, _glAttachShader, glAttachShader);
	LOAD_PROC(PFNGLDELETEBUFFERSPROC, _glDeleteBuffers, glDeleteBuffers);
	LOAD_PROC(PFNGLCOMPILESHADERPROC, _glCompileShader, glCompileShader);
	LOAD_PROC(PFNGLCREATEPROGRAMPROC, _glCreateProgram, glCreateProgram);
	LOAD_PROC(PFNGLDELETEPROGRAMPROC, _glDeleteProgram, glDeleteProgram);
	LOAD_PROC(PFNGLGENVERTEXARRAYSPROC, _glGenVertexArrays, glGenVertexArrays);
	LOAD_PROC(PFNGLBINDVERTEXARRAYPROC, _glBindVertexArray, glBindVertexArray);
	LOAD_PROC(PFNGLDELETEVERTEXARRAYSPROC, _glDeleteVertexArrays, glDeleteVertexArrays);
	LOAD_PROC(PFNGLVERTEXATTRIBPOINTERPROC, _glVertexAttribPointer, glVertexAttribPointer);
	LOAD_PROC(PFNGLENABLEVERTEXATTRIBARRAYPROC, _glEnableVertexAttribArray, glEnableVertexAttribArray);
	return true;
}

GLFWwindow *init_opengl(void)
{
	if (!glfwInit())
		return NULL;
	
	GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return NULL;
	}
	glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_TRUE);
	glfwMakeContextCurrent(window);
	if (!load_opengl_functions()) {
		glfwDestroyWindow(window);
		glfwTerminate();
		return NULL;
	}
	return window;
}
