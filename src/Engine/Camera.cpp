#include "Camera.h"

Camera::Camera() :
	fov(80),
	nearClipPlane(0.1f),
	farClipPlane(100)
{
}

glm::mat4 Camera::ViewMatrix() const
{
	return glm::lookAt(position, target, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Camera::ProjectionMatrix() const
{
	return glm::perspective(fov, Constants::AspectRatio(), nearClipPlane, farClipPlane);
}

glm::vec3 Camera::UpVector() const
{
	return ViewMatrix() * glm::vec4(0, 1, 0, 0);
}

glm::vec3 Camera::RightVector() const
{
	return ViewMatrix() * glm::vec4(1, 0, 0, 0);
}

glm::vec3 Camera::DirectionVector() const
{
	return glm::normalize(target - position);
}

void Camera::SetPosition(glm::vec3&& position)
{
	this->position = position;
}

void Camera::SetTarget(glm::vec3&& target)
{
	this->target = target;
}

void Camera::Zoom(float deltaDistance)
{
	glm::vec3 distanceV = position - target;
	float distance = glm::length(distanceV);
	float ratio = (distance + deltaDistance) / distance;
	distanceV *= ratio;
	position = target + distanceV;
}

void Camera::RotateAround(float x, float y)
{

}
