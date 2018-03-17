#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
	glId = gl::glCreateProgram();
	gl::glAttachShader(glId, vertexShader);
	gl::glAttachShader(glId, fragmentShader);
	gl::glLinkProgram(glId);

	int success;
	glGetProgramiv(glId, gl::GLenum::GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		gl::glGetProgramInfoLog(glId, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	else std::cout << "Shader program linked successfully\n";
}

const unsigned& ShaderProgram::GlId() const
{
	return glId;
}
