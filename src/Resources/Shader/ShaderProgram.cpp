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

void ShaderProgram::SetVec3(std::string name, glm::vec3 value) const
{
	const unsigned location = gl::glGetUniformLocation(glId, name.c_str());
	gl::glUniform3f(location, value.x, value.y, value.z);
}

const unsigned& ShaderProgram::GlId() const
{
	return glId;
}
