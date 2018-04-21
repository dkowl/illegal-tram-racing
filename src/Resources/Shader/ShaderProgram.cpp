#include "ShaderProgram.h"
#include "../../Utils.h"

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

void ShaderProgram::Use()
{
	gl::glUseProgram(glId);
}

void ShaderProgram::SetVec3(std::string name, glm::vec3 value) const
{
	const int location = gl::glGetUniformLocation(glId, name.c_str());
	std::cout << "location " << location << " " << name << " is ";
	Utils::DisplayVec3(value);
	gl::glUniform3f(location, value.x, value.y, value.z);
}

void ShaderProgram::SetFloat(std::string name, float value) const
{
	const int location = gl::glGetUniformLocation(glId, name.c_str());
	gl::glUniform1f(location, value);
}

const unsigned& ShaderProgram::GlId() const
{
	return glId;
}
