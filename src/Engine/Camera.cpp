#include "Camera.h"

Camera::Camera() :
	mode(Mode::PITCH_YAW),
	target(0, 0, 0),
	position(0, 20, 20),
	yaw(0),
	pitch(30),
	minPitch(0),
	maxPitch(89),
	distance(40),
	minDistance(0.1f),
	maxDistance(100),
	fov(80),
	nearClipPlane(0.1f),
	farClipPlane(1000)
{
}

glm::mat4 Camera::ViewMatrix() const
{
	switch (mode) {
	case Mode::POSITION:
		return glm::lookAt(position, target, glm::vec3(0.0f, 1.0f, 0.0f));
	case Mode::PITCH_YAW:
	{
		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(0, 0, distance));

		glm::mat4 yawMat;
		yawMat = glm::rotate(yawMat, glm::radians(yaw), glm::vec3(0, 1, 0));
		glm::vec3 rightVector = yawMat * glm::vec4(1, 0, 0, 1);

		glm::mat4 pitchMat;
		pitchMat = glm::rotate(pitchMat, glm::radians(-pitch), rightVector);

		//glm::mat4 rollMat;
		//rollMat = glm::rotate(rollMat, glm::radians(180.f), glm::vec3(0, 0, -1));

		glm::vec3 newPosition = pitchMat * yawMat * trans * glm::vec4(target, 1);
		Utils::DisplayVec3(newPosition);
		return glm::lookAt(newPosition, target, glm::vec3(0, 1, 0));
	}
	}
}

glm::mat4 Camera::ProjectionMatrix() const
{
	return glm::perspective(glm::radians(fov), Constants::AspectRatio(), nearClipPlane, farClipPlane);
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

void Camera::SetMode(Mode mode)
{
	this->mode = mode;
}

void Camera::SetPosition(glm::vec3&& position)
{
	this->position = position;
}

void Camera::SetYaw(float yawDegrees)
{
	yaw = yawDegrees;
}

void Camera::SetPitch(float pitchDegrees)
{
	pitch = glm::clamp(pitchDegrees, minPitch, maxPitch);
}

void Camera::SetMinPitch(float minPitch)
{
	this->minPitch = minPitch;
}

void Camera::SetMaxPitch(float maxPitch)
{
	this->maxPitch = maxPitch;
}

void Camera::SetTarget(glm::vec3&& target)
{
	this->target = target;
}

void Camera::SetDistance(float distance)
{
	this->distance = glm::clamp(distance, minDistance, maxDistance);
}

void Camera::SetMinDistance(float minDistance)
{
	this->minDistance = minDistance;
}

void Camera::SetMaxDistance(float maxDistance)
{
	this->maxDistance = maxDistance;
}

void Camera::Zoom(float deltaDistance)
{
	switch (mode) {
	case Mode::POSITION:
	{
		glm::vec3 distanceV = position - target;
		float distance = glm::length(distanceV);
		float ratio = (distance + deltaDistance) / distance;
		distanceV *= ratio;
		position = target + distanceV;
	}
		break;
	case Mode::PITCH_YAW:
		SetDistance(this->distance + deltaDistance);
		break;
	}
}

void Camera::RotateAround(float deltaYaw, float deltaPitch)
{
	switch (mode) {
	case Mode::POSITION: 
	{
		glm::vec3 distanceV = position - target;
		glm::mat4 transformMatrix;
		//transformMatrix = glm::translate(transformMatrix, distanceV);
		transformMatrix = glm::rotate(transformMatrix, glm::radians(deltaYaw), glm::vec3(0, 1, 0));
		transformMatrix = glm::rotate(transformMatrix, glm::radians(deltaPitch), glm::vec3(1, 0, 0));
		Utils::DisplayVec3(position);
		position = transformMatrix * glm::vec4(distanceV, 0) + glm::vec4(target, 0);
		Utils::DisplayVec3(position);
	}
		break;
	case Mode::PITCH_YAW:
		SetYaw(yaw + deltaYaw);
		SetPitch(pitch + deltaPitch);
		break;
	}
}
