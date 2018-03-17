#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Constants.h"
#include "../Utils.h"

class Camera
{
public:
	enum class Mode
	{
		POSITION,
		PITCH_YAW
	};

private:
	Mode mode;

	glm::vec3 target;

	glm::vec3 position;

	float yaw;
	float pitch;
	float minPitch;
	float maxPitch;
	float distance;
	float minDistance;
	float maxDistance;

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

	void SetMode(Mode mode);

	void SetTarget(glm::vec3 &&target);

	void SetPosition(glm::vec3 &&position);

	void SetYaw(float yawDegrees);
	void SetPitch(float pitchDegrees);
	void SetMinPitch(float minPitch);
	void SetMaxPitch(float maxPitch);
	void SetDistance(float distance);
	void SetMinDistance(float minDistance);
	void SetMaxDistance(float maxDistance);

	void Zoom(float deltaDistance);
	void RotateAround(float deltaYaw, float deltaPitch);
};