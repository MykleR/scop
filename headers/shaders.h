#pragma once
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <assert.h>
#include <stdbool.h>

#define LOAD_PROC(type, var, name) \
    var = (type)glfwGetProcAddress(#name); \
	if (!var) return false; \

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

typedef enum e_shader_type {
	SHADER_VERTEX,
	SHADER_FRAGMENT,
	SHADER_GEOMETRY,
	SHADER_COMPUTE,
} shader_type_t;

GLFWwindow *init_opengl(void);

GLuint compile_shader(GLenum type, const char* src);

GLuint create_shader_program(const char* vsrc, const char* fsrc);

