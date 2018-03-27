#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
protected:
	glm::vec3 screenshakeOffset;

public:
	Camera();

	virtual glm::mat4 ViewMatrix() const = 0;
	virtual glm::mat4 ProjectionMatrix() const = 0;

	void SetScreenshakeOffset(const glm::vec3 &offset);
};