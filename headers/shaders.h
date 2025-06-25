#pragma once
#include <GLFW/glfw3.h>
#include <assert.h>
#include <stdbool.h>

#define LOAD_PROC(type, name) \
    name = (type)glfwGetProcAddress(#name); \
	if (!name) return false; \

// Function pointer types for OpenGL functions we need
typedef void (*GL_GENVERTEXARRAYS)(GLsizei, GLuint*);
typedef void (*GL_BINDVERTEXARRAY)(GLuint);
typedef void (*GL_GENBUFFERS)(GLsizei, GLuint*);
typedef void (*GL_BINDBUFFER)(GLenum, GLuint);
typedef void (*GL_BUFFERDATA)(GLenum, ptrdiff_t, const void*, GLenum);
typedef void (*GL_VERTEXATTRIBPOINTER)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void*);
typedef void (*GL_ENABLEVERTEXATTRIBARRAY)(GLuint);
typedef GLuint (*GL_CREATESHADER)(GLenum);
typedef void (*GL_SHADER_SOURCE)(GLuint, GLsizei, const GLchar* const*, const GLint*);
typedef void (*GL_COMPILESHADER)(GLuint);
typedef GLuint (*GL_CREATEPROGRAM)(void);
typedef void (*GL_ATTACHSHADER)(GLuint, GLuint);
typedef void (*GL_LINKPROGRAM)(GLuint);
typedef void (*GL_USEPROGRAM)(GLuint);
typedef void (*GL_DELETEVERTEXARRAYS)(GLsizei, const GLuint*);
typedef void (*GL_DELETEBUFFERS)(GLsizei, const GLuint*);
typedef void (*GL_DELETEPROGRAM)(GLuint);
typedef void (*GL_DELETESHADER)(GLuint);

extern GL_GENVERTEXARRAYS glGenVertexArrays;
extern GL_BINDVERTEXARRAY glBindVertexArray;
extern GL_GENBUFFERS glGenBuffers;
extern GL_BINDBUFFER glBindBuffer;
extern GL_BUFFERDATA glBufferData;
extern GL_VERTEXATTRIBPOINTER glVertexAttribPointer;
extern GL_ENABLEVERTEXATTRIBARRAY glEnableVertexAttribArray;
extern GL_CREATESHADER glCreateShader;
extern GL_SHADER_SOURCE glShaderSource;
extern GL_COMPILESHADER glCompileShader;
extern GL_CREATEPROGRAM glCreateProgram;
extern GL_ATTACHSHADER glAttachShader;
extern GL_LINKPROGRAM glLinkProgram;
extern GL_USEPROGRAM glUseProgram;
extern GL_DELETEVERTEXARRAYS glDeleteVertexArrays;
extern GL_DELETEBUFFERS glDeleteBuffers;
extern GL_DELETEPROGRAM glDeleteProgram;
extern GL_DELETESHADER glDeleteShader;

typedef enum e_shader_type {
	SHADER_VERTEX,
	SHADER_FRAGMENT,
	SHADER_GEOMETRY,
	SHADER_COMPUTE,
} shader_type_t;

GLFWwindow *init_opengl(void);

GLuint compile_shader(GLenum type, const char* src);

GLuint create_shader_program(const char* vsrc, const char* fsrc);

