#pragma once
#include <string>
#include <iostream>

#include "../../glbinding.h"

#include "../../Libraries/stb_image.h"

#include "../../Constants.h"

class Texture
{
	static const std::string TEXTURE_RESOURCE_PATH;

	int width;
	int height;
	int channelCount;

	unsigned int glId;
	
public:
	Texture(const std::string &filename);
};