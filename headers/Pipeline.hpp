#pragma once

#include <GL/glew.h>
#include <boost/iostreams/device/mapped_file.hpp> // for mmap

#include <debug.hpp>
#include <utils.hpp>

#define SHADER_LOG_LENGTH 512

class Pipeline
{
GETTER(GLuint, id)

EXCEPTION(PipelineCreationException, "Pipeline creation failed")
EXCEPTION(ShaderCreationException, "Shader creation failed")
EXCEPTION(ShaderSourceException, "Shader source loading failed")
EXCEPTION_MSG(ShaderCompileException)
EXCEPTION_MSG(ShaderLinkException)

public:
	Pipeline() : _id(0) {};
	virtual ~Pipeline();

	void addShader(const std::string& path, GLenum type);
	void linkProgram();

	static GLuint compileShader(const std::string& path, GLenum type);
};
