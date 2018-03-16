#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Constants.h"

class Camera
{
	glm::vec3 position;
	glm::vec3 target;

	float fov;
	float nearClipPlane;
	float farClipPlane;

public:
	Camera();

	glm::mat4 ViewMatrix() const;
	glm::mat4 ProjectionMatrix() const;

	glm::vec3 UpVector() const;
	glm::vec3 RightVector() const;
	glm::vec3 DirectionVector() const;

	void SetPosition(glm::vec3 &&position);
	void SetTarget(glm::vec3 &&target);

	void Zoom(float deltaDistance);
	void RotateAround(float x, float y);
};