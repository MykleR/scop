#pragma once

# include <GLFW/glfw3.h>
# include <GL/gl.h>
# include <assert.h>
# include <stdio.h>

# include <debug.h>

# define ERR_CODE 0
# define OK_CODE 1

# define VERTEX_SSRC "#version 330 core\n"\
"layout(location = 0) in vec3 aPos;\n"\
"layout(location = 1) in vec3 aColor;\n"\
"layout(location = 2) in vec2 aTexCoord;\n"\
"out vec3 ourColor;\n"\
"out vec2 TexCoord;\n"\
"void main() {\n"\
"    gl_Position = vec4(aPos, 1.0);\n"\
"    ourColor = aColor;\n"\
"    TexCoord = aTexCoord;\n"\
"}"

# define FRAGMENT_SSRC "#version 330 core\n"\
"in vec3 ourColor;\n"\
"in vec2 TexCoord;\n"\
"out vec4 FragColor;\n"\
"void main() {\n"\
"   FragColor = vec4(ourColor, 1.0);\n"\
"}"

# define __LOAD_PROC(type, var, name) \
    var = (type)glfwGetProcAddress(#name); \
	if (!var) return 0; \

# define __SHADER_ERROR(type, shader) { \
	char log[512]; \
	_glGetShaderInfoLog(shader, 512, NULL, log); \
	LOG_ERR("Shader compile error: %s", log); \
	return ERR_CODE; }

# define __PROGRAM_ERROR(program) { \
	char log[512]; \
	_glGetProgramInfoLog(program, 512, NULL, log); \
	LOG_ERR("Program link error: %s", log); \
	return ERR_CODE; }

extern PFNGLCREATESHADERPROC			_glCreateShader;
extern PFNGLSHADERSOURCEPROC			_glShaderSource;
extern PFNGLCOMPILESHADERPROC			_glCompileShader;
extern PFNGLCREATEPROGRAMPROC			_glCreateProgram;
extern PFNGLATTACHSHADERPROC			_glAttachShader;
extern PFNGLLINKPROGRAMPROC				_glLinkProgram;
extern PFNGLUSEPROGRAMPROC				_glUseProgram;
extern PFNGLGENVERTEXARRAYSPROC			_glGenVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC			_glBindVertexArray;
extern PFNGLGENBUFFERSPROC				_glGenBuffers;
extern PFNGLBINDBUFFERPROC				_glBindBuffer;
extern PFNGLBUFFERDATAPROC				_glBufferData;
extern PFNGLVERTEXATTRIBPOINTERPROC		_glVertexAttribPointer;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC	_glEnableVertexAttribArray;
extern PFNGLDELETEVERTEXARRAYSPROC		_glDeleteVertexArrays;
extern PFNGLDELETEBUFFERSPROC			_glDeleteBuffers;
extern PFNGLDELETEPROGRAMPROC			_glDeleteProgram;
extern PFNGLDELETESHADERPROC			_glDeleteShader;
extern PFNGLGETSHADERIVPROC				_glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC		_glGetShaderInfoLog;
extern PFNGLGETPROGRAMIVPROC			_glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC		_glGetProgramInfoLog;
extern PFNGLGETUNIFORMLOCATIONPROC		_glGetUniformLocation;
extern PFNGLUNIFORM2FVPROC				_glUniform2fv;
extern PFNGLUNIFORM1FPROC				_glUniform1f;

typedef enum e_shader_type {
	SHADER_VERTEX,
	SHADER_FRAGMENT,
	SHADER_GEOMETRY,
	SHADER_COMPUTE,
} shader_type_t;

GLFWwindow *init_opengl(void);

int	shader_load(GLenum type, const char* src, GLuint* out_shader);

int	shader_program(const char* vsrc, const char* fsrc, GLuint* out_program);
