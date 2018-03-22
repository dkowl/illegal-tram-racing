#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	virtual glm::mat4 ViewMatrix() const = 0;
	virtual glm::mat4 ProjectionMatrix() const = 0;
};