#include "Texture.h"

Texture::Texture(const std::string& filename)
{
	unsigned char *data = stbi_load((TEXTURE_RESOURCE_PATH + filename).c_str(), &width, &height, &channelCount, 0);
	if(data)
	{
		gl::GLenum type;
		if (channelCount == 3) type = gl::GLenum::GL_RGB;
		else if (channelCount == 4) type = gl::GLenum::GL_RGBA;
		else
		{
			std::cout << "ERROR::TEXTURE: Mumber of color channels not supported (" << channelCount << ")\n";
			return;
		}

		gl::glGenTextures(1, &glId);
		gl::glBindTexture(gl::GLenum::GL_TEXTURE_2D, glId);
		gl::glTexParameteri(gl::GLenum::GL_TEXTURE_2D, gl::GLenum::GL_TEXTURE_WRAP_S, gl::GLenum::GL_REPEAT);
		gl::glTexParameteri(gl::GLenum::GL_TEXTURE_2D, gl::GLenum::GL_TEXTURE_WRAP_T, gl::GLenum::GL_REPEAT);
		gl::glTexParameteri(gl::GLenum::GL_TEXTURE_2D, gl::GLenum::GL_TEXTURE_MIN_FILTER, gl::GLenum::GL_LINEAR);
		gl::glTexParameteri(gl::GLenum::GL_TEXTURE_2D, gl::GLenum::GL_TEXTURE_MAG_FILTER, gl::GLenum::GL_LINEAR);
		gl::glTexImage2D(gl::GLenum::GL_TEXTURE_2D, 0, type, width, height, 0, type, gl::GLenum::GL_UNSIGNED_BYTE, data);
		gl::glGenerateMipmap(gl::GLenum::GL_TEXTURE_2D);
		std::cout << "texture " << filename << " loaded successfully\n";
		std::cout << "width: " << width << std::endl;
		std::cout << "height: " << height << std::endl;
		std::cout << "channels: " << channelCount << std::endl;
	}
	else
	{
		std::cout << "Failed to load texture " << filename << std::endl;
	}
	stbi_image_free(data);
}

const unsigned& Texture::GlId() const
{
	return glId;
}

const std::string Texture::TEXTURE_RESOURCE_PATH = Constants::RESOURCE_PATH + "Textures/";

