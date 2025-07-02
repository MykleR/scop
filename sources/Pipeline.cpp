#include <Pipeline.hpp>

Pipeline::~Pipeline()
{
	if (_id)
		glDeleteProgram(_id);
}

void Pipeline::linkProgram()
{
	GLchar	log[SHADER_LOG_LENGTH];
	GLint	success;
	glLinkProgram(_id);
	glGetProgramiv(_id, GL_LINK_STATUS, &success);
	glGetProgramInfoLog(_id, SHADER_LOG_LENGTH, nullptr, log);
	if (!success)
		throw ShaderLinkException(log);
	LOG_OK("Pipeline linked successfully");
}

void Pipeline::addShader(const std::string& path, GLenum type)
{

	if (!_id && !(_id = glCreateProgram()))
		throw PipelineCreationException();
	try {
		GLuint shaderId = compileShader(path, type);
		glAttachShader(_id, shaderId);
		glDeleteShader(shaderId);
	} CATCH_RET();
	LOG_DEBUG("Shader %s added to pipeline", path.c_str());
}

GLuint Pipeline::compileShader(const std::string& path, GLenum type)
{
	GLuint id = glCreateShader(type);
	if (!id)
		throw ShaderCreationException();

	boost::iostreams::mapped_file mmap(path, boost::iostreams::mapped_file::readonly);
	if (!mmap.is_open())
		throw ShaderSourceException();

	const char* source = mmap.const_data();
	glShaderSource(id, 1, &source, nullptr);
	glCompileShader(id);

	GLint success;
	GLchar infoLog[SHADER_LOG_LENGTH];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	glGetShaderInfoLog(id, SHADER_LOG_LENGTH, nullptr, infoLog);
	if (!success)
		throw ShaderCompileException(infoLog);
	return id;
}
