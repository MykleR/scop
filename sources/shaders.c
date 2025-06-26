#include <GL/gl.h>
#include <shaders.h>
#include <stdio.h>

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
PFNGLGETSHADERIVPROC				_glGetShaderiv = NULL;
PFNGLGETSHADERINFOLOGPROC			_glGetShaderInfoLog = NULL;
PFNGLGETPROGRAMIVPROC				_glGetProgramiv = NULL;
PFNGLGETPROGRAMINFOLOGPROC			_glGetProgramInfoLog = NULL;
PFNGLGETUNIFORMLOCATIONPROC			_glGetUniformLocation = NULL;
PFNGLUNIFORM2FVPROC					_glUniform2fv = NULL;
PFNGLUNIFORM1FPROC					_glUniform1f = NULL;

static int load_opengl_functions(void)
{
	__LOAD_PROC(PFNGLGENBUFFERSPROC, _glGenBuffers, glGenBuffers);
	__LOAD_PROC(PFNGLBINDBUFFERPROC, _glBindBuffer, glBindBuffer);
	__LOAD_PROC(PFNGLBUFFERDATAPROC, _glBufferData, glBufferData);
	__LOAD_PROC(PFNGLUSEPROGRAMPROC, _glUseProgram, glUseProgram);
	__LOAD_PROC(PFNGLGETSHADERIVPROC, _glGetShaderiv, glGetShaderiv);
	__LOAD_PROC(PFNGLLINKPROGRAMPROC, _glLinkProgram, glLinkProgram);
	__LOAD_PROC(PFNGLCREATESHADERPROC, _glCreateShader, glCreateShader);
	__LOAD_PROC(PFNGLDELETESHADERPROC, _glDeleteShader, glDeleteShader);
	__LOAD_PROC(PFNGLSHADERSOURCEPROC, _glShaderSource, glShaderSource);
	__LOAD_PROC(PFNGLATTACHSHADERPROC, _glAttachShader, glAttachShader);
	__LOAD_PROC(PFNGLDELETEBUFFERSPROC, _glDeleteBuffers, glDeleteBuffers);
	__LOAD_PROC(PFNGLCOMPILESHADERPROC, _glCompileShader, glCompileShader);
	__LOAD_PROC(PFNGLCREATEPROGRAMPROC, _glCreateProgram, glCreateProgram);
	__LOAD_PROC(PFNGLDELETEPROGRAMPROC, _glDeleteProgram, glDeleteProgram);
	__LOAD_PROC(PFNGLGENVERTEXARRAYSPROC, _glGenVertexArrays, glGenVertexArrays);
	__LOAD_PROC(PFNGLBINDVERTEXARRAYPROC, _glBindVertexArray, glBindVertexArray);
	__LOAD_PROC(PFNGLGETSHADERINFOLOGPROC, _glGetShaderInfoLog, glGetShaderInfoLog);
	__LOAD_PROC(PFNGLDELETEVERTEXARRAYSPROC, _glDeleteVertexArrays, glDeleteVertexArrays);
	__LOAD_PROC(PFNGLVERTEXATTRIBPOINTERPROC, _glVertexAttribPointer, glVertexAttribPointer);
	__LOAD_PROC(PFNGLENABLEVERTEXATTRIBARRAYPROC, _glEnableVertexAttribArray, glEnableVertexAttribArray);
	__LOAD_PROC(PFNGLGETPROGRAMIVPROC, _glGetProgramiv, glGetProgramiv);
	__LOAD_PROC(PFNGLGETPROGRAMINFOLOGPROC, _glGetProgramInfoLog, glGetProgramInfoLog);
	__LOAD_PROC(PFNGLGETUNIFORMLOCATIONPROC, _glGetUniformLocation, glGetUniformLocation);
	__LOAD_PROC(PFNGLUNIFORM2FVPROC, _glUniform2fv, glUniform2fv);
	__LOAD_PROC(PFNGLUNIFORM1FPROC, _glUniform1f, glUniform1f);
	return 1;
}

GLFWwindow *init_opengl(void)
{
	if (!glfwInit())
		return NULL;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
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

int	shader_load(GLenum type, const char *src, GLuint *out_shader)
{
    int		success;
	GLuint	shader = _glCreateShader(type);
    _glShaderSource(shader, 1, &src, NULL);
    _glCompileShader(shader);
    _glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) __SHADER_ERROR(type, shader);
	if (out_shader) *out_shader = shader;
    return OK_CODE;
}

int shader_program(const char* vsrc, const char* fsrc, GLuint *out_prog)
{
	GLuint	vs, fs, prog;
    int		success;
	if (shader_load(GL_VERTEX_SHADER, vsrc, &vs) == ERR_CODE || 
		shader_load(GL_FRAGMENT_SHADER, fsrc, &fs) == ERR_CODE)
		return ERR_CODE;
    prog = _glCreateProgram();
    _glAttachShader(prog, vs);
    _glAttachShader(prog, fs);
    _glLinkProgram(prog);
    _glGetProgramiv(prog, GL_LINK_STATUS, &success);
    _glDeleteShader(vs);
    _glDeleteShader(fs);
    if (!success) __PROGRAM_ERROR(prog);
	if (out_prog) *out_prog = prog;
    return OK_CODE;
}
